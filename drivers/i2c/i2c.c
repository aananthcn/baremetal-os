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

#include "i2c.h"

/* ---- Local helpers ---- */

static void wait_flag(I2C_TypeDef *i2c, u32 sr1_mask) {
    while (!(i2c->SR1 & sr1_mask));
}

static void send_start(I2C_TypeDef *i2c) {
    i2c->CR1 |= (1u << 8);             /* START bit */
    wait_flag(i2c, (1u << 0));          /* SB: start condition generated */
}

static void send_stop(I2C_TypeDef *i2c) {
    i2c->CR1 |= (1u << 9);             /* STOP bit */
}

static void send_addr(I2C_TypeDef *i2c, u8 addr, int read) {
    i2c->DR = (u8)((addr << 1) | (read ? 1u : 0u));
    wait_flag(i2c, (1u << 1));          /* ADDR: address sent */
    (void)i2c->SR1;                     /* clear ADDR by reading SR1 then SR2 */
    (void)i2c->SR2;
}


/* ---- Master ---- */

void i2c_master_init(I2C_TypeDef *i2c, u32 pclk_hz, u32 speed_hz) {
    u32 cr2_freq = pclk_hz / 1000000u;  /* FREQ field = APB1 MHz */

    i2c->CR1 &= ~(1u << 0);            /* disable peripheral */
    i2c->CR2  =  cr2_freq & 0x3Fu;
    i2c->CCR  =  pclk_hz / (speed_hz * 2u);  /* standard mode (Sm) */
    i2c->TRISE = cr2_freq + 1u;
    i2c->CR1 |=  (1u << 0);            /* enable peripheral */
}

int i2c_master_write(I2C_TypeDef *i2c, u8 addr, const u8 *data, u16 len) {
    send_start(i2c);
    send_addr(i2c, addr, 0);

    for (u16 i = 0; i < len; i++) {
        i2c->DR = data[i];
        wait_flag(i2c, (1u << 7));     /* TXE: data register empty */
    }

    wait_flag(i2c, (1u << 2));         /* BTF: byte transfer finished */
    send_stop(i2c);
    return 0;
}

int i2c_master_read(I2C_TypeDef *i2c, u8 addr, u8 *data, u16 len) {
    if (len == 0) return 0;

    i2c->CR1 |= (1u << 10);            /* ACK enable */
    send_start(i2c);
    send_addr(i2c, addr, 1);

    for (u16 i = 0; i < len; i++) {
        if (i == len - 1u) {
            i2c->CR1 &= ~(1u << 10);   /* NACK last byte */
            send_stop(i2c);
        }
        wait_flag(i2c, (1u << 6));     /* RXNE: data register not empty */
        data[i] = (u8)i2c->DR;
    }
    return 0;
}


/* ---- Slave ---- */

void i2c_slave_init(I2C_TypeDef *i2c, u8 own_addr) {
    i2c->CR1 &= ~(1u << 0);            /* disable peripheral */
    i2c->OAR1 = (u32)(own_addr << 1);  /* 7-bit address in bits [7:1] */
    i2c->CR1 |=  (1u << 10);           /* ACK enable */
    i2c->CR1 |=  (1u << 0);            /* enable peripheral */
}

u8 i2c_slave_read(I2C_TypeDef *i2c) {
    /* Wait for address match, then for data */
    while (!(i2c->SR1 & (1u << 1)));   /* ADDR */
    (void)i2c->SR1;
    (void)i2c->SR2;

    wait_flag(i2c, (1u << 6));         /* RXNE */
    return (u8)i2c->DR;
}

void i2c_slave_write(I2C_TypeDef *i2c, u8 data) {
    wait_flag(i2c, (1u << 7));         /* TXE */
    i2c->DR = data;
}
