#ifndef UART_H
#define UART_H

#include <stm32f407vet6/stm32f407vet6.h>

/* Peripheral init — call once after board_init() */
void uart1_init(void);

/* TX */
void uart1_putchar(char c);
void uart1_puts(const char *s);

/* RX */
char uart1_getchar(void);

#endif
