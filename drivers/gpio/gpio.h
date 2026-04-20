#ifndef GPIO_H
#define GPIO_H

#include <stm32f407vet6/stm32f407vet6.h>

void gpio_enable_clock(GPIO_TypeDef *gpio);
void gpio_set_output(GPIO_TypeDef *gpio, int pin);
void gpio_write(GPIO_TypeDef *gpio, int pin, int value);

#endif