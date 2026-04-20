#include "uart.h"


/* ---- USART1 SR / CR1 bits ---- */

#define SR_TXE      (1u << 7)   /* transmit data register empty */
#define SR_RXNE     (1u << 5)   /* receive data register not empty */
#define CR1_UE      (1u << 13)  /* USART enable */
#define CR1_TE      (1u <<  3)  /* transmitter enable */
#define CR1_RE      (1u <<  2)  /* receiver enable */

/*
 * APB2 = 84 MHz, target 115200 baud, oversampling by 16:
 *   USARTDIV = 84 000 000 / (16 × 115 200) = 45.572
 *   Mantissa = 45  (0x2D)
 *   Fraction = round(0.572 × 16) = 9
 *   BRR      = (45 << 4) | 9 = 0x2D9   → actual 115 226 baud (<0.03 % error)
 */
#define BRR_115200  0x2D9u


void uart1_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    USART1->BRR = BRR_115200;
    USART1->CR1 = CR1_UE | CR1_TE | CR1_RE;
}

void uart1_putchar(char c) {
    while (!(USART1->SR & SR_TXE));
    USART1->DR = (u32)(unsigned char)c;
}

void uart1_puts(const char *s) {
    while (*s)
        uart1_putchar(*s++);
}

char uart1_getchar(void) {
    while (!(USART1->SR & SR_RXNE));
    return (char)(USART1->DR & 0xFF);
}
