#include "gpio.h"

void gpio_enable_clock(GPIO_TypeDef *gpio)
{
    if (gpio == GPIOA)
        RCC->AHB1ENR |= (1 << 0);

    if (gpio == GPIOB)
        RCC->AHB1ENR |= (1 << 1);

    if (gpio == GPIOC)
        RCC->AHB1ENR |= (1 << 2);
}

void gpio_set_output(GPIO_TypeDef *gpio, int pin)
{
    gpio->MODER &= ~(3 << (pin * 2));
    gpio->MODER |=  (1 << (pin * 2));
}

void gpio_write(GPIO_TypeDef *gpio, int pin, int value)
{
    if (value)
        gpio->BSRR = (1 << pin);
    else
        gpio->BSRR = (1 << (pin + 16));
}