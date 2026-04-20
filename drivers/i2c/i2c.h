#ifndef I2C_H
#define I2C_H

#include <stm32f407vet6/stm32f407vet6.h>

/* Master mode */
void    i2c_master_init(I2C_TypeDef *i2c, u32 pclk_hz, u32 speed_hz);
int     i2c_master_write(I2C_TypeDef *i2c, u8 addr, const u8 *data, u16 len);
int     i2c_master_read(I2C_TypeDef *i2c, u8 addr, u8 *data, u16 len);

/* Slave mode */
void    i2c_slave_init(I2C_TypeDef *i2c, u8 own_addr);
u8      i2c_slave_read(I2C_TypeDef *i2c);
void    i2c_slave_write(I2C_TypeDef *i2c, u8 data);

#endif /* I2C_H */
