/*
 * Copyright 2026 Aananth C N
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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