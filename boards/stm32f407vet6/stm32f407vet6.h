#ifndef STM32F407VET6_H
#define STM32F407VET6_H

#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;


/* ============================================================
   BUS BASE ADDRESSES  (RM0090 Table 1)
   ============================================================ */

#define PERIPH_BASE         0x40000000UL
#define APB1PERIPH_BASE     0x40000000UL
#define APB2PERIPH_BASE     0x40010000UL
#define AHB1PERIPH_BASE     0x40020000UL
#define AHB2PERIPH_BASE     0x50000000UL
#define AHB3PERIPH_BASE     0x60000000UL

/* Core private peripherals (inside the Cortex-M4 itself) */
#define CORE_PERIPH_BASE    0xE0000000UL


/* ============================================================
   APB1 PERIPHERAL BASE ADDRESSES
   ============================================================ */

#define TIM2_BASE           0x40000000UL
#define TIM3_BASE           0x40000400UL
#define TIM4_BASE           0x40000800UL
#define TIM5_BASE           0x40000C00UL
#define TIM6_BASE           0x40001000UL
#define TIM7_BASE           0x40001400UL
#define TIM12_BASE          0x40001800UL
#define TIM13_BASE          0x40001C00UL
#define TIM14_BASE          0x40002000UL
#define RTC_BASE            0x40002800UL
#define WWDG_BASE           0x40002C00UL
#define IWDG_BASE           0x40003000UL
#define SPI2_BASE           0x40003800UL
#define SPI3_BASE           0x40003C00UL
#define USART2_BASE         0x40004400UL
#define USART3_BASE         0x40004800UL
#define UART4_BASE          0x40004C00UL
#define UART5_BASE          0x40005000UL
#define I2C1_BASE           0x40005400UL
#define I2C2_BASE           0x40005800UL
#define I2C3_BASE           0x40005C00UL
#define CAN1_BASE           0x40006400UL
#define CAN2_BASE           0x40006800UL
#define PWR_BASE            0x40007000UL
#define DAC_BASE            0x40007400UL


/* ============================================================
   APB2 PERIPHERAL BASE ADDRESSES
   ============================================================ */

#define TIM1_BASE           0x40010000UL
#define TIM8_BASE           0x40010400UL
#define USART1_BASE         0x40011000UL
#define USART6_BASE         0x40011400UL
#define ADC1_BASE           0x40012000UL
#define ADC2_BASE           0x40012100UL
#define ADC3_BASE           0x40012200UL
#define ADC_COMMON_BASE     0x40012300UL
#define SDIO_BASE           0x40012C00UL
#define SPI1_BASE           0x40013000UL
#define SYSCFG_BASE         0x40013800UL
#define EXTI_BASE           0x40013C00UL
#define TIM9_BASE           0x40014000UL
#define TIM10_BASE          0x40014400UL
#define TIM11_BASE          0x40014800UL


/* ============================================================
   AHB1 PERIPHERAL BASE ADDRESSES
   ============================================================ */

#define GPIOA_BASE          0x40020000UL
#define GPIOB_BASE          0x40020400UL
#define GPIOC_BASE          0x40020800UL
#define GPIOD_BASE          0x40020C00UL
#define GPIOE_BASE          0x40021000UL
#define GPIOF_BASE          0x40021400UL
#define GPIOG_BASE          0x40021800UL
#define GPIOH_BASE          0x40021C00UL
#define GPIOI_BASE          0x40022000UL
#define CRC_BASE            0x40023000UL
#define RCC_BASE            0x40023800UL
#define FLASH_R_BASE        0x40023C00UL   /* Flash interface registers, not Flash memory */
#define DMA1_BASE           0x40026000UL
#define DMA1_S0_BASE        0x40026010UL
#define DMA1_S1_BASE        0x40026028UL
#define DMA1_S2_BASE        0x40026040UL
#define DMA1_S3_BASE        0x40026058UL
#define DMA1_S4_BASE        0x40026070UL
#define DMA1_S5_BASE        0x40026088UL
#define DMA1_S6_BASE        0x400260A0UL
#define DMA1_S7_BASE        0x400260B8UL
#define DMA2_BASE           0x40026400UL
#define DMA2_S0_BASE        0x40026410UL
#define DMA2_S1_BASE        0x40026428UL
#define DMA2_S2_BASE        0x40026440UL
#define DMA2_S3_BASE        0x40026458UL
#define DMA2_S4_BASE        0x40026470UL
#define DMA2_S5_BASE        0x40026488UL
#define DMA2_S6_BASE        0x400264A0UL
#define DMA2_S7_BASE        0x400264B8UL


/* ============================================================
   CORTEX-M4 CORE PERIPHERAL BASE ADDRESSES  (ARMv7-M ARM B3.2)
   ============================================================ */

#define SYSTICK_BASE        0xE000E010UL
#define NVIC_BASE           0xE000E100UL
#define SCB_BASE            0xE000ED00UL


/* ============================================================
   IRQ NUMBERS  (RM0090 Table 61)
   ============================================================ */

typedef enum {
    /* Cortex-M4 processor exceptions */
    NMI_IRQn                    = -14,
    MemManage_IRQn              = -12,
    BusFault_IRQn               = -11,
    UsageFault_IRQn             = -10,
    SVCall_IRQn                 =  -5,
    DebugMon_IRQn               =  -4,
    PendSV_IRQn                 =  -2,
    SysTick_IRQn                =  -1,
    /* STM32F407 external interrupts */
    WWDG_IRQn                   =   0,
    PVD_IRQn                    =   1,
    TAMP_STAMP_IRQn             =   2,
    RTC_WKUP_IRQn               =   3,
    FLASH_IRQn                  =   4,
    RCC_IRQn                    =   5,
    EXTI0_IRQn                  =   6,
    EXTI1_IRQn                  =   7,
    EXTI2_IRQn                  =   8,
    EXTI3_IRQn                  =   9,
    EXTI4_IRQn                  =  10,
    DMA1_Stream0_IRQn           =  11,
    DMA1_Stream1_IRQn           =  12,
    DMA1_Stream2_IRQn           =  13,
    DMA1_Stream3_IRQn           =  14,
    DMA1_Stream4_IRQn           =  15,
    DMA1_Stream5_IRQn           =  16,
    DMA1_Stream6_IRQn           =  17,
    ADC_IRQn                    =  18,
    CAN1_TX_IRQn                =  19,
    CAN1_RX0_IRQn               =  20,
    CAN1_RX1_IRQn               =  21,
    CAN1_SCE_IRQn               =  22,
    EXTI9_5_IRQn                =  23,
    TIM1_BRK_TIM9_IRQn          =  24,
    TIM1_UP_TIM10_IRQn          =  25,
    TIM1_TRG_COM_TIM11_IRQn     =  26,
    TIM1_CC_IRQn                =  27,
    TIM2_IRQn                   =  28,
    TIM3_IRQn                   =  29,
    TIM4_IRQn                   =  30,
    I2C1_EV_IRQn                =  31,
    I2C1_ER_IRQn                =  32,
    I2C2_EV_IRQn                =  33,
    I2C2_ER_IRQn                =  34,
    SPI1_IRQn                   =  35,
    SPI2_IRQn                   =  36,
    USART1_IRQn                 =  37,
    USART2_IRQn                 =  38,
    USART3_IRQn                 =  39,
    EXTI15_10_IRQn              =  40,
    RTC_Alarm_IRQn              =  41,
    OTG_FS_WKUP_IRQn            =  42,
    TIM8_BRK_TIM12_IRQn         =  43,
    TIM8_UP_TIM13_IRQn          =  44,
    TIM8_TRG_COM_TIM14_IRQn     =  45,
    TIM8_CC_IRQn                =  46,
    DMA1_Stream7_IRQn           =  47,
    FSMC_IRQn                   =  48,
    SDIO_IRQn                   =  49,
    TIM5_IRQn                   =  50,
    SPI3_IRQn                   =  51,
    UART4_IRQn                  =  52,
    UART5_IRQn                  =  53,
    TIM6_DAC_IRQn               =  54,
    TIM7_IRQn                   =  55,
    DMA2_Stream0_IRQn           =  56,
    DMA2_Stream1_IRQn           =  57,
    DMA2_Stream2_IRQn           =  58,
    DMA2_Stream3_IRQn           =  59,
    DMA2_Stream4_IRQn           =  60,
    ETH_IRQn                    =  61,
    ETH_WKUP_IRQn               =  62,
    CAN2_TX_IRQn                =  63,
    CAN2_RX0_IRQn               =  64,
    CAN2_RX1_IRQn               =  65,
    CAN2_SCE_IRQn               =  66,
    OTG_FS_IRQn                 =  67,
    DMA2_Stream5_IRQn           =  68,
    DMA2_Stream6_IRQn           =  69,
    DMA2_Stream7_IRQn           =  70,
    USART6_IRQn                 =  71,
    I2C3_EV_IRQn                =  72,
    I2C3_ER_IRQn                =  73,
    OTG_HS_EP1_OUT_IRQn         =  74,
    OTG_HS_EP1_IN_IRQn          =  75,
    OTG_HS_WKUP_IRQn            =  76,
    OTG_HS_IRQn                 =  77,
    DCMI_IRQn                   =  78,
    CRYP_IRQn                   =  79,
    HASH_RNG_IRQn               =  80,
    FPU_IRQn                    =  81,
} IRQn_Type;


/* ============================================================
   GPIO (RM0090 §8.4)
   ============================================================ */

typedef struct {
    volatile u32 MODER;     /* 0x00 - Mode (input/output/AF/analog per pin) */
    volatile u32 OTYPER;    /* 0x04 - Output type (push-pull / open-drain) */
    volatile u32 OSPEEDR;   /* 0x08 - Output speed */
    volatile u32 PUPDR;     /* 0x0C - Pull-up / pull-down */
    volatile u32 IDR;       /* 0x10 - Input data (read-only) */
    volatile u32 ODR;       /* 0x14 - Output data */
    volatile u32 BSRR;      /* 0x18 - Bit set/reset (upper half = reset) */
    volatile u32 LCKR;      /* 0x1C - Configuration lock */
    volatile u32 AFRL;      /* 0x20 - Alternate function pins 0-7 */
    volatile u32 AFRH;      /* 0x24 - Alternate function pins 8-15 */
} GPIO_TypeDef;

#define GPIOA   ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB   ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC   ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD   ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE   ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF   ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG   ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH   ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI   ((GPIO_TypeDef *) GPIOI_BASE)


/* ============================================================
   RCC (RM0090 §6.3)
   ============================================================ */

typedef struct {
    volatile u32 CR;            /* 0x00 - Clock control */
    volatile u32 PLLCFGR;      /* 0x04 - PLL configuration */
    volatile u32 CFGR;          /* 0x08 - Clock configuration */
    volatile u32 CIR;           /* 0x0C - Clock interrupt */
    volatile u32 AHB1RSTR;     /* 0x10 - AHB1 peripheral reset */
    volatile u32 AHB2RSTR;     /* 0x14 - AHB2 peripheral reset */
    volatile u32 AHB3RSTR;     /* 0x18 - AHB3 peripheral reset */
    u32          _res0;         /* 0x1C */
    volatile u32 APB1RSTR;     /* 0x20 - APB1 peripheral reset */
    volatile u32 APB2RSTR;     /* 0x24 - APB2 peripheral reset */
    u32          _res1[2];      /* 0x28-0x2C */
    volatile u32 AHB1ENR;      /* 0x30 - AHB1 peripheral clock enable */
    volatile u32 AHB2ENR;      /* 0x34 - AHB2 peripheral clock enable */
    volatile u32 AHB3ENR;      /* 0x38 - AHB3 peripheral clock enable */
    u32          _res2;         /* 0x3C */
    volatile u32 APB1ENR;      /* 0x40 - APB1 peripheral clock enable */
    volatile u32 APB2ENR;      /* 0x44 - APB2 peripheral clock enable */
    u32          _res3[2];      /* 0x48-0x4C */
    volatile u32 AHB1LPENR;    /* 0x50 - AHB1 clock enable in low-power mode */
    volatile u32 AHB2LPENR;    /* 0x54 - AHB2 clock enable in low-power mode */
    volatile u32 AHB3LPENR;    /* 0x58 - AHB3 clock enable in low-power mode */
    u32          _res4;         /* 0x5C */
    volatile u32 APB1LPENR;    /* 0x60 - APB1 clock enable in low-power mode */
    volatile u32 APB2LPENR;    /* 0x64 - APB2 clock enable in low-power mode */
    u32          _res5[2];      /* 0x68-0x6C */
    volatile u32 BDCR;          /* 0x70 - Backup domain control */
    volatile u32 CSR;           /* 0x74 - Clock control & status */
    u32          _res6[2];      /* 0x78-0x7C */
    volatile u32 SSCGR;         /* 0x80 - Spread-spectrum clock generation */
    volatile u32 PLLI2SCFGR;   /* 0x84 - PLLI2S configuration */
} RCC_TypeDef;

#define RCC     ((RCC_TypeDef *) RCC_BASE)

/* RCC AHB1ENR clock-enable bits */
#define RCC_AHB1ENR_GPIOAEN     (1u <<  0)
#define RCC_AHB1ENR_GPIOBEN     (1u <<  1)
#define RCC_AHB1ENR_GPIOCEN     (1u <<  2)
#define RCC_AHB1ENR_GPIODEN     (1u <<  3)
#define RCC_AHB1ENR_GPIOEEN     (1u <<  4)
#define RCC_AHB1ENR_GPIOFEN     (1u <<  5)
#define RCC_AHB1ENR_GPIOGEN     (1u <<  6)
#define RCC_AHB1ENR_GPIOHEN     (1u <<  7)
#define RCC_AHB1ENR_GPIOIEN     (1u <<  8)
#define RCC_AHB1ENR_CRCEN       (1u << 12)
#define RCC_AHB1ENR_DMA1EN      (1u << 21)
#define RCC_AHB1ENR_DMA2EN      (1u << 22)

/* RCC APB1ENR clock-enable bits */
#define RCC_APB1ENR_TIM2EN      (1u <<  0)
#define RCC_APB1ENR_TIM3EN      (1u <<  1)
#define RCC_APB1ENR_TIM4EN      (1u <<  2)
#define RCC_APB1ENR_TIM5EN      (1u <<  3)
#define RCC_APB1ENR_TIM6EN      (1u <<  4)
#define RCC_APB1ENR_TIM7EN      (1u <<  5)
#define RCC_APB1ENR_SPI2EN      (1u << 14)
#define RCC_APB1ENR_SPI3EN      (1u << 15)
#define RCC_APB1ENR_USART2EN    (1u << 17)
#define RCC_APB1ENR_USART3EN    (1u << 18)
#define RCC_APB1ENR_UART4EN     (1u << 19)
#define RCC_APB1ENR_UART5EN     (1u << 20)
#define RCC_APB1ENR_I2C1EN      (1u << 21)
#define RCC_APB1ENR_I2C2EN      (1u << 22)
#define RCC_APB1ENR_I2C3EN      (1u << 23)
#define RCC_APB1ENR_PWREN       (1u << 28)
#define RCC_APB1ENR_DACEN       (1u << 29)

/* RCC APB2ENR clock-enable bits */
#define RCC_APB2ENR_TIM1EN      (1u <<  0)
#define RCC_APB2ENR_TIM8EN      (1u <<  1)
#define RCC_APB2ENR_USART1EN    (1u <<  4)
#define RCC_APB2ENR_USART6EN    (1u <<  5)
#define RCC_APB2ENR_ADC1EN      (1u <<  8)
#define RCC_APB2ENR_ADC2EN      (1u <<  9)
#define RCC_APB2ENR_ADC3EN      (1u << 10)
#define RCC_APB2ENR_SPI1EN      (1u << 12)
#define RCC_APB2ENR_SYSCFGEN    (1u << 14)
#define RCC_APB2ENR_TIM9EN      (1u << 16)
#define RCC_APB2ENR_TIM10EN     (1u << 17)
#define RCC_APB2ENR_TIM11EN     (1u << 18)


/* ============================================================
   USART / UART (RM0090 §30.6)
   ============================================================ */

typedef struct {
    volatile u32 SR;    /* 0x00 - Status */
    volatile u32 DR;    /* 0x04 - Data */
    volatile u32 BRR;   /* 0x08 - Baud rate */
    volatile u32 CR1;   /* 0x0C - Control 1 */
    volatile u32 CR2;   /* 0x10 - Control 2 */
    volatile u32 CR3;   /* 0x14 - Control 3 */
    volatile u32 GTPR;  /* 0x18 - Guard time and prescaler */
} USART_TypeDef;

#define USART1  ((USART_TypeDef *) USART1_BASE)
#define USART2  ((USART_TypeDef *) USART2_BASE)
#define USART3  ((USART_TypeDef *) USART3_BASE)
#define UART4   ((USART_TypeDef *) UART4_BASE)
#define UART5   ((USART_TypeDef *) UART5_BASE)
#define USART6  ((USART_TypeDef *) USART6_BASE)


/* ============================================================
   I2C (RM0090 §27.6)
   ============================================================ */

typedef struct {
    volatile u32 CR1;   /* 0x00 - Control 1 */
    volatile u32 CR2;   /* 0x04 - Control 2 */
    volatile u32 OAR1;  /* 0x08 - Own address 1 */
    volatile u32 OAR2;  /* 0x0C - Own address 2 */
    volatile u32 DR;    /* 0x10 - Data */
    volatile u32 SR1;   /* 0x14 - Status 1 */
    volatile u32 SR2;   /* 0x18 - Status 2 */
    volatile u32 CCR;   /* 0x1C - Clock control */
    volatile u32 TRISE; /* 0x20 - Rise time */
    volatile u32 FLTR;  /* 0x24 - Digital noise filter */
} I2C_TypeDef;

#define I2C1    ((I2C_TypeDef *) I2C1_BASE)
#define I2C2    ((I2C_TypeDef *) I2C2_BASE)
#define I2C3    ((I2C_TypeDef *) I2C3_BASE)


/* ============================================================
   SPI / I2S (RM0090 §28.5)
   ============================================================ */

typedef struct {
    volatile u32 CR1;       /* 0x00 - Control 1 (not used in I2S mode) */
    volatile u32 CR2;       /* 0x04 - Control 2 */
    volatile u32 SR;        /* 0x08 - Status */
    volatile u32 DR;        /* 0x0C - Data */
    volatile u32 CRCPR;     /* 0x10 - CRC polynomial */
    volatile u32 RXCRCR;    /* 0x14 - RX CRC */
    volatile u32 TXCRCR;    /* 0x18 - TX CRC */
    volatile u32 I2SCFGR;   /* 0x1C - I2S configuration */
    volatile u32 I2SPR;     /* 0x20 - I2S prescaler */
} SPI_TypeDef;

#define SPI1    ((SPI_TypeDef *) SPI1_BASE)
#define SPI2    ((SPI_TypeDef *) SPI2_BASE)
#define SPI3    ((SPI_TypeDef *) SPI3_BASE)


/* ============================================================
   Timers (RM0090 §17-23)

   Single struct covers all GP and advanced timers.
   RCR is valid only on TIM1/TIM8 (advanced); reserved on TIM2-5.
   BDTR is valid only on TIM1/TIM8 (advanced); reserved on TIM2-5.
   OR (option register) is timer-specific; not all timers implement it.
   ============================================================ */

typedef struct {
    volatile u32 CR1;   /* 0x00 - Control 1 */
    volatile u32 CR2;   /* 0x04 - Control 2 */
    volatile u32 SMCR;  /* 0x08 - Slave mode control */
    volatile u32 DIER;  /* 0x0C - DMA/interrupt enable */
    volatile u32 SR;    /* 0x10 - Status */
    volatile u32 EGR;   /* 0x14 - Event generation */
    volatile u32 CCMR1; /* 0x18 - Capture/compare mode 1 */
    volatile u32 CCMR2; /* 0x1C - Capture/compare mode 2 */
    volatile u32 CCER;  /* 0x20 - Capture/compare enable */
    volatile u32 CNT;   /* 0x24 - Counter */
    volatile u32 PSC;   /* 0x28 - Prescaler */
    volatile u32 ARR;   /* 0x2C - Auto-reload */
    volatile u32 RCR;   /* 0x30 - Repetition counter (TIM1/8 only) */
    volatile u32 CCR1;  /* 0x34 - Capture/compare 1 */
    volatile u32 CCR2;  /* 0x38 - Capture/compare 2 */
    volatile u32 CCR3;  /* 0x3C - Capture/compare 3 */
    volatile u32 CCR4;  /* 0x40 - Capture/compare 4 */
    volatile u32 BDTR;  /* 0x44 - Break and dead-time (TIM1/8 only) */
    volatile u32 DCR;   /* 0x48 - DMA control */
    volatile u32 DMAR;  /* 0x4C - DMA address for full transfer */
    volatile u32 OR;    /* 0x50 - Timer option (TIM2/5/11 specific) */
} TIM_TypeDef;

#define TIM1    ((TIM_TypeDef *) TIM1_BASE)
#define TIM2    ((TIM_TypeDef *) TIM2_BASE)
#define TIM3    ((TIM_TypeDef *) TIM3_BASE)
#define TIM4    ((TIM_TypeDef *) TIM4_BASE)
#define TIM5    ((TIM_TypeDef *) TIM5_BASE)
#define TIM6    ((TIM_TypeDef *) TIM6_BASE)
#define TIM7    ((TIM_TypeDef *) TIM7_BASE)
#define TIM8    ((TIM_TypeDef *) TIM8_BASE)
#define TIM9    ((TIM_TypeDef *) TIM9_BASE)
#define TIM10   ((TIM_TypeDef *) TIM10_BASE)
#define TIM11   ((TIM_TypeDef *) TIM11_BASE)
#define TIM12   ((TIM_TypeDef *) TIM12_BASE)
#define TIM13   ((TIM_TypeDef *) TIM13_BASE)
#define TIM14   ((TIM_TypeDef *) TIM14_BASE)


/* ============================================================
   ADC (RM0090 §13.13)
   ============================================================ */

typedef struct {
    volatile u32 SR;        /* 0x00 - Status */
    volatile u32 CR1;       /* 0x04 - Control 1 */
    volatile u32 CR2;       /* 0x08 - Control 2 */
    volatile u32 SMPR1;     /* 0x0C - Sample time 1 (channels 10-18) */
    volatile u32 SMPR2;     /* 0x10 - Sample time 2 (channels 0-9) */
    volatile u32 JOFR1;     /* 0x14 - Injected channel data offset 1 */
    volatile u32 JOFR2;     /* 0x18 - Injected channel data offset 2 */
    volatile u32 JOFR3;     /* 0x1C - Injected channel data offset 3 */
    volatile u32 JOFR4;     /* 0x20 - Injected channel data offset 4 */
    volatile u32 HTR;       /* 0x24 - Watchdog higher threshold */
    volatile u32 LTR;       /* 0x28 - Watchdog lower threshold */
    volatile u32 SQR1;      /* 0x2C - Regular sequence 1 (length + ch 13-16) */
    volatile u32 SQR2;      /* 0x30 - Regular sequence 2 (ch 7-12) */
    volatile u32 SQR3;      /* 0x34 - Regular sequence 3 (ch 1-6) */
    volatile u32 JSQR;      /* 0x38 - Injected sequence */
    volatile u32 JDR1;      /* 0x3C - Injected data 1 */
    volatile u32 JDR2;      /* 0x40 - Injected data 2 */
    volatile u32 JDR3;      /* 0x44 - Injected data 3 */
    volatile u32 JDR4;      /* 0x48 - Injected data 4 */
    volatile u32 DR;        /* 0x4C - Regular data */
} ADC_TypeDef;

typedef struct {
    volatile u32 CSR;   /* 0x00 - Common status */
    volatile u32 CCR;   /* 0x04 - Common control */
    volatile u32 CDR;   /* 0x08 - Common regular data (dual/triple modes) */
} ADC_Common_TypeDef;

#define ADC1        ((ADC_TypeDef *)        ADC1_BASE)
#define ADC2        ((ADC_TypeDef *)        ADC2_BASE)
#define ADC3        ((ADC_TypeDef *)        ADC3_BASE)
#define ADC_COMMON  ((ADC_Common_TypeDef *) ADC_COMMON_BASE)


/* ============================================================
   DMA (RM0090 §10.5)
   ============================================================ */

typedef struct {
    volatile u32 CR;    /* 0x00 - Stream configuration */
    volatile u32 NDTR;  /* 0x04 - Number of data items */
    volatile u32 PAR;   /* 0x08 - Peripheral address */
    volatile u32 M0AR;  /* 0x0C - Memory 0 address */
    volatile u32 M1AR;  /* 0x10 - Memory 1 address (double-buffer mode) */
    volatile u32 FCR;   /* 0x14 - FIFO control */
} DMA_Stream_TypeDef;

typedef struct {
    volatile u32 LISR;  /* 0x00 - Low interrupt status (streams 0-3) */
    volatile u32 HISR;  /* 0x04 - High interrupt status (streams 4-7) */
    volatile u32 LIFCR; /* 0x08 - Low interrupt flag clear */
    volatile u32 HIFCR; /* 0x0C - High interrupt flag clear */
} DMA_TypeDef;

#define DMA1            ((DMA_TypeDef *)        DMA1_BASE)
#define DMA1_Stream0    ((DMA_Stream_TypeDef *)  DMA1_S0_BASE)
#define DMA1_Stream1    ((DMA_Stream_TypeDef *)  DMA1_S1_BASE)
#define DMA1_Stream2    ((DMA_Stream_TypeDef *)  DMA1_S2_BASE)
#define DMA1_Stream3    ((DMA_Stream_TypeDef *)  DMA1_S3_BASE)
#define DMA1_Stream4    ((DMA_Stream_TypeDef *)  DMA1_S4_BASE)
#define DMA1_Stream5    ((DMA_Stream_TypeDef *)  DMA1_S5_BASE)
#define DMA1_Stream6    ((DMA_Stream_TypeDef *)  DMA1_S6_BASE)
#define DMA1_Stream7    ((DMA_Stream_TypeDef *)  DMA1_S7_BASE)
#define DMA2            ((DMA_TypeDef *)        DMA2_BASE)
#define DMA2_Stream0    ((DMA_Stream_TypeDef *)  DMA2_S0_BASE)
#define DMA2_Stream1    ((DMA_Stream_TypeDef *)  DMA2_S1_BASE)
#define DMA2_Stream2    ((DMA_Stream_TypeDef *)  DMA2_S2_BASE)
#define DMA2_Stream3    ((DMA_Stream_TypeDef *)  DMA2_S3_BASE)
#define DMA2_Stream4    ((DMA_Stream_TypeDef *)  DMA2_S4_BASE)
#define DMA2_Stream5    ((DMA_Stream_TypeDef *)  DMA2_S5_BASE)
#define DMA2_Stream6    ((DMA_Stream_TypeDef *)  DMA2_S6_BASE)
#define DMA2_Stream7    ((DMA_Stream_TypeDef *)  DMA2_S7_BASE)


/* ============================================================
   EXTI (RM0090 §12.3)
   ============================================================ */

typedef struct {
    volatile u32 IMR;   /* 0x00 - Interrupt mask */
    volatile u32 EMR;   /* 0x04 - Event mask */
    volatile u32 RTSR;  /* 0x08 - Rising trigger selection */
    volatile u32 FTSR;  /* 0x0C - Falling trigger selection */
    volatile u32 SWIER; /* 0x10 - Software interrupt event */
    volatile u32 PR;    /* 0x14 - Pending */
} EXTI_TypeDef;

#define EXTI    ((EXTI_TypeDef *) EXTI_BASE)


/* ============================================================
   SYSCFG (RM0090 §9.2)
   ============================================================ */

typedef struct {
    volatile u32 MEMRMP;    /* 0x00 - Memory remap */
    volatile u32 PMC;       /* 0x04 - Peripheral mode configuration */
    volatile u32 EXTICR[4]; /* 0x08-0x14 - External interrupt configuration */
    u32          _res[2];   /* 0x18-0x1C */
    volatile u32 CMPCR;     /* 0x20 - Compensation cell control */
} SYSCFG_TypeDef;

#define SYSCFG  ((SYSCFG_TypeDef *) SYSCFG_BASE)


/* ============================================================
   PWR (RM0090 §5.4)
   ============================================================ */

typedef struct {
    volatile u32 CR;    /* 0x00 - Power control */
    volatile u32 CSR;   /* 0x04 - Power control/status */
} PWR_TypeDef;

#define PWR     ((PWR_TypeDef *) PWR_BASE)


/* ============================================================
   Flash interface (RM0090 §3.9)
   ============================================================ */

typedef struct {
    volatile u32 ACR;       /* 0x00 - Access control (flash latency) */
    volatile u32 KEYR;      /* 0x04 - Key register (unlock flash CR) */
    volatile u32 OPTKEYR;   /* 0x08 - Option byte key */
    volatile u32 SR;        /* 0x0C - Status */
    volatile u32 CR;        /* 0x10 - Control */
    volatile u32 OPTCR;     /* 0x14 - Option control */
} FLASH_TypeDef;

#define FLASH_IFACE ((FLASH_TypeDef *) FLASH_R_BASE)


/* ============================================================
   SysTick (ARMv7-M ARM §B3.3)
   ============================================================ */

typedef struct {
    volatile u32 CTRL;  /* 0x00 - Control and status */
    volatile u32 LOAD;  /* 0x04 - Reload value */
    volatile u32 VAL;   /* 0x08 - Current value */
    volatile u32 CALIB; /* 0x0C - Calibration */
} SysTick_TypeDef;

#define SYSTICK ((SysTick_TypeDef *) SYSTICK_BASE)

/* SysTick CTRL bits */
#define SYSTICK_CTRL_ENABLE     (1u <<  0)  /* Counter enable */
#define SYSTICK_CTRL_TICKINT    (1u <<  1)  /* Assert SysTick exception on underflow */
#define SYSTICK_CTRL_CLKSOURCE  (1u <<  2)  /* 0 = external ref, 1 = processor clock */
#define SYSTICK_CTRL_COUNTFLAG  (1u << 16)  /* Set to 1 when counter reaches 0 */


/* ============================================================
   NVIC (ARMv7-M ARM §B3.4)
   ============================================================ */

typedef struct {
    volatile u32 ISER[8];   /* 0x000 - Interrupt set-enable */
    u32          _res0[24]; /* 0x020-0x07F */
    volatile u32 ICER[8];   /* 0x080 - Interrupt clear-enable */
    u32          _res1[24]; /* 0x0A0-0x0FF */
    volatile u32 ISPR[8];   /* 0x100 - Interrupt set-pending */
    u32          _res2[24]; /* 0x120-0x17F */
    volatile u32 ICPR[8];   /* 0x180 - Interrupt clear-pending */
    u32          _res3[24]; /* 0x1A0-0x1FF */
    volatile u32 IABR[8];   /* 0x200 - Interrupt active-bit */
    u32          _res4[56]; /* 0x220-0x2FF */
    volatile u8  IP[240];   /* 0x300 - Interrupt priority (one byte per IRQ) */
    u8           _res5[16]; /* 0x3F0-0x3FF */
    u32          _res6[640];/* 0x400-0xDFF */
    volatile u32 STIR;      /* 0xE00 - Software trigger interrupt */
} NVIC_TypeDef;

#define NVIC    ((NVIC_TypeDef *) NVIC_BASE)

/* NVIC helper macros — irqn must be a non-negative IRQn_Type value */
#define NVIC_ENABLE_IRQ(irqn)           (NVIC->ISER[(irqn) >> 5] =  (1u << ((irqn) & 0x1F)))
#define NVIC_DISABLE_IRQ(irqn)          (NVIC->ICER[(irqn) >> 5] =  (1u << ((irqn) & 0x1F)))
#define NVIC_SET_PENDING(irqn)          (NVIC->ISPR[(irqn) >> 5] =  (1u << ((irqn) & 0x1F)))
#define NVIC_CLEAR_PENDING(irqn)        (NVIC->ICPR[(irqn) >> 5] =  (1u << ((irqn) & 0x1F)))
#define NVIC_SET_PRIORITY(irqn, prio)   (NVIC->IP[(irqn)] = (u8)(prio))


/* ============================================================
   SCB (ARMv7-M ARM §B3.2)
   ============================================================ */

typedef struct {
    volatile u32 CPUID;     /* 0x00 - CPU ID base */
    volatile u32 ICSR;      /* 0x04 - Interrupt control and state */
    volatile u32 VTOR;      /* 0x08 - Vector table offset */
    volatile u32 AIRCR;     /* 0x0C - Application interrupt and reset control */
    volatile u32 SCR;       /* 0x10 - System control */
    volatile u32 CCR;       /* 0x14 - Configuration and control */
    volatile u8  SHPR[12];  /* 0x18 - System handler priority (byte access) */
    volatile u32 SHCSR;     /* 0x24 - System handler control and state */
    volatile u32 CFSR;      /* 0x28 - Configurable fault status */
    volatile u32 HFSR;      /* 0x2C - HardFault status */
    volatile u32 DFSR;      /* 0x30 - Debug fault status */
    volatile u32 MMFAR;     /* 0x34 - MemManage fault address */
    volatile u32 BFAR;      /* 0x38 - BusFault address */
    volatile u32 AFSR;      /* 0x3C - Auxiliary fault status */
    u32          _res[18];  /* 0x40-0x84 */
    volatile u32 CPACR;     /* 0x88 - Coprocessor access control (FPU enable) */
} SCB_TypeDef;

#define SCB     ((SCB_TypeDef *) SCB_BASE)

/* SCB AIRCR key — must be written to bits [31:16] when modifying AIRCR */
#define SCB_AIRCR_VECTKEY       (0x05FAu << 16)
#define SCB_AIRCR_SYSRESETREQ   (1u << 2)   /* Request system reset */

/* SCB CPACR — enable FPU (CP10 and CP11 full access) */
#define SCB_CPACR_FPU_ENABLE    ((3u << 20) | (3u << 22))


#endif /* STM32F407VET6_H */
