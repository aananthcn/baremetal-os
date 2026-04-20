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
