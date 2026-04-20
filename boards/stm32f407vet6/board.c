#include <stm32f407vet6/stm32f407vet6.h>

/*
 * System clock after board_init(): 168 MHz from HSI via PLL.
 *
 *   HSI (16 MHz) → /PLLM(8) → 2 MHz VCO input
 *                → ×PLLN(168) → 336 MHz VCO output
 *                → /PLLP(2)  → 168 MHz SYSCLK
 *                → /PLLQ(7)  →  48 MHz USB / SDIO / RNG
 *
 *   AHB  = SYSCLK / 1 = 168 MHz
 *   APB1 = AHB    / 4 =  42 MHz  (peripheral max: 42 MHz)
 *   APB2 = AHB    / 2 =  84 MHz  (peripheral max: 84 MHz)
 */
u32 SystemCoreClock = 168000000;

/* ---- Local bit-field helpers ---- */

/* Flash ACR */
#define FLASH_ACR_PRFTEN    (1u <<  8)
#define FLASH_ACR_ICEN      (1u <<  9)
#define FLASH_ACR_DCEN      (1u << 10)

/* RCC CR */
#define RCC_CR_HSION        (1u <<  0)
#define RCC_CR_HSIRDY       (1u <<  1)
#define RCC_CR_PLLON        (1u << 24)
#define RCC_CR_PLLRDY       (1u << 25)

/* RCC CFGR SW / SWS */
#define RCC_CFGR_SW_PLL     (2u <<  0)
#define RCC_CFGR_SWS_MASK   (3u <<  2)
#define RCC_CFGR_SWS_PLL    (2u <<  2)
#define RCC_CFGR_PPRE1_DIV4 (5u << 10)   /* APB1 prescaler ÷4 */
#define RCC_CFGR_PPRE2_DIV2 (4u << 13)   /* APB2 prescaler ÷2 */


/*
 * PA13=JTMS, PA14=JTCK, PA15=JTDI are AF0 (JTAG) at reset, but a bootloader
 * may reconfigure them. Re-assert AF mode + correct pull resistors explicitly
 * so JTAG is always available regardless of prior boot state.
 *
 * PB4 (NJTRST) and PB3 (JTDO) are not touched here — add them if needed.
 *
 * RM0090 Table 9: PA13 pull-up, PA14 pull-down, PA15 pull-up.
 * AF0 = 0x0 (system function), selected via AFRH bits; MODER = 10 (AF mode).
 */
static void jtag_init(void) {
    RCC->AHB1ENR |= (1u << 0);   /* GPIOA clock enable */

    /* MODER[31:26]: set PA15, PA14, PA13 to AF mode (0b10 each) */
    GPIOA->MODER &= ~((3u << 30) | (3u << 28) | (3u << 26));
    GPIOA->MODER |=   (2u << 30) | (2u << 28) | (2u << 26);

    /* AFRH: AF0 (= 0x0) for PA15 [31:28], PA14 [27:24], PA13 [23:20] */
    GPIOA->AFRH  &= ~((0xFu << 28) | (0xFu << 24) | (0xFu << 20));
    /* AF0 = 0, no OR step needed */

    /* PUPDR: PA13 pull-up (01), PA14 pull-down (10), PA15 pull-up (01) */
    GPIOA->PUPDR &= ~((3u << 30) | (3u << 28) | (3u << 26));
    GPIOA->PUPDR |=   (1u << 30) | (2u << 28) | (1u << 26);
}


/*
 * PA9=USART1_TX, PA10=USART1_RX — AF7 (USART1/2/3).
 * Pin mux only; baud-rate and peripheral enable are done in uart1_init().
 *
 * AFRH offsets: PA9 → bits [7:4]  ((9-8)*4=4)
 *               PA10 → bits [11:8] ((10-8)*4=8)
 * MODER bits:   PA9  → [19:18], PA10 → [21:20]   (pin × 2)
 */
static void usart1_pin_init(void) {
    RCC->AHB1ENR |= (1u << 0);   /* GPIOA clock (may already be on) */

    /* MODER: PA9 and PA10 to AF mode (0b10) */
    GPIOA->MODER &= ~((3u << 18) | (3u << 20));
    GPIOA->MODER |=   (2u << 18) | (2u << 20);

    /* AFRH: AF7 for PA9 [7:4] and PA10 [11:8] */
    GPIOA->AFRH  &= ~((0xFu <<  4) | (0xFu <<  8));
    GPIOA->AFRH  |=   (7u   <<  4) | (7u   <<  8);

    /* OSPEEDR: high speed on TX (PA9) to keep edges clean at 115200 */
    GPIOA->OSPEEDR &= ~(3u << 18);
    GPIOA->OSPEEDR |=  (2u << 18);

    /* PUPDR: pull-up on RX (PA10) so the line is not floating when idle */
    GPIOA->PUPDR &= ~(3u << 20);
    GPIOA->PUPDR |=  (1u << 20);
}


static void clock_init(void) {
    /* 1. Ensure HSI is on and ready (it is at reset, but be explicit) */
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    /* 2. Set flash latency to 5 WS before raising SYSCLK above 150 MHz
     *    (RM0090 §3.4, Table 10: VCORE 2.7–3.6 V, f > 150 MHz → 5 WS) */
    FLASH_IFACE->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | 5u;

    /* 3. Configure PLL — must be done while PLL is off */
    RCC->CR &= ~RCC_CR_PLLON;

    RCC->PLLCFGR = (8u   <<  0)   /* PLLM  = 8  → VCO input 2 MHz  */
                 | (168u <<  6)   /* PLLN  = 168 → VCO output 336 MHz */
                 | (0u   << 16)   /* PLLP  = 00 → ÷2 = 168 MHz SYSCLK */
                 | (0u   << 22)   /* PLLSRC = 0 → HSI */
                 | (7u   << 24);  /* PLLQ  = 7  → 48 MHz USB clock */

    /* 4. Enable PLL and wait for lock */
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    /* 5. Set APB bus prescalers before switching SYSCLK */
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;

    /* 6. Switch SYSCLK to PLL and wait for the hardware to confirm */
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL);
}


/*
 * Configure SysTick to fire every (SystemCoreClock / ticks_per_second) cycles.
 * The systick_handler() in vector_handlers.c is weak — override it in your
 * application or kernel to implement the OS tick.
 */
void systick_config(u32 ticks_per_second) {
    u32 reload = (SystemCoreClock / ticks_per_second) - 1u;
    SYSTICK->LOAD = reload;
    SYSTICK->VAL  = 0u;
    SYSTICK->CTRL = SYSTICK_CTRL_CLKSOURCE   /* processor clock */
                  | SYSTICK_CTRL_TICKINT     /* assert SysTick exception */
                  | SYSTICK_CTRL_ENABLE;
}


/*
 * Called from startup.c immediately after .data / .bss initialisation,
 * before main().
 */
void board_init(void) {
    jtag_init();
    clock_init();
    usart1_pin_init();
}
