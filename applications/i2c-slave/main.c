#include <drivers/i2c/i2c.h>

int main()
{
    i2c_slave_init(I2C1, 0x42);

    while (1)
    {
        uint8_t data = i2c_slave_read(I2C1);
    }
}