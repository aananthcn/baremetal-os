#include <drivers/gpio/gpio.h>

int main()
{
    gpio_enable_clock(GPIOA);
    gpio_set_output(GPIOA, 6);
    gpio_set_output(GPIOA, 7);

    while (1)
    {
        gpio_write(GPIOA, 6, 1);
        gpio_write(GPIOA, 7, 0);

        for (volatile int i = 0; i < 500000; i++);

        gpio_write(GPIOA, 6, 0);
        gpio_write(GPIOA, 7, 1);

        for (volatile int i = 0; i < 500000; i++);
    }
}