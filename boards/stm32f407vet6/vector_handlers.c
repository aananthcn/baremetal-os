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

/*
 * Default (weak) exception and IRQ handlers.
 *
 * Every handler is an alias for default_handler(), which spins forever so
 * that an unhandled fault is immediately visible in the debugger.
 *
 * Override any handler in your application or driver by defining a function
 * with the same name — the linker will prefer the strong definition.
 *
 * Example:
 *   void tim2_irq_handler(void) { ... }
 */

void default_handler(void) {
    for (;;);
}

/* ---- Cortex-M4 processor exceptions ---- */

void nmi_handler(void)          __attribute__((weak, alias("default_handler")));
void hardfault_handler(void)    __attribute__((weak, alias("default_handler")));
void memmanage_handler(void)    __attribute__((weak, alias("default_handler")));
void busfault_handler(void)     __attribute__((weak, alias("default_handler")));
void usagefault_handler(void)   __attribute__((weak, alias("default_handler")));
void svcall_handler(void)       __attribute__((weak, alias("default_handler")));
void debugmon_handler(void)     __attribute__((weak, alias("default_handler")));
void pendsv_handler(void)       __attribute__((weak, alias("default_handler")));
void systick_handler(void)      __attribute__((weak, alias("default_handler")));

/* ---- STM32F407 external IRQs (RM0090 Table 61) ---- */

void wwdg_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void pvd_irq_handler(void)              __attribute__((weak, alias("default_handler")));
void tamp_stamp_irq_handler(void)       __attribute__((weak, alias("default_handler")));
void rtc_wkup_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void flash_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void rcc_irq_handler(void)              __attribute__((weak, alias("default_handler")));
void exti0_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void exti1_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void exti2_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void exti3_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void exti4_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void dma1_stream0_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma1_stream1_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma1_stream2_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma1_stream3_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma1_stream4_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma1_stream5_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma1_stream6_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void adc_irq_handler(void)              __attribute__((weak, alias("default_handler")));
void can1_tx_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void can1_rx0_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void can1_rx1_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void can1_sce_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void exti9_5_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void tim1_brk_tim9_irq_handler(void)    __attribute__((weak, alias("default_handler")));
void tim1_up_tim10_irq_handler(void)    __attribute__((weak, alias("default_handler")));
void tim1_trg_com_tim11_irq_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_cc_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void tim2_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void tim3_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void tim4_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void i2c1_ev_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void i2c1_er_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void i2c2_ev_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void i2c2_er_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void spi1_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void spi2_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void usart1_irq_handler(void)           __attribute__((weak, alias("default_handler")));
void usart2_irq_handler(void)           __attribute__((weak, alias("default_handler")));
void usart3_irq_handler(void)           __attribute__((weak, alias("default_handler")));
void exti15_10_irq_handler(void)        __attribute__((weak, alias("default_handler")));
void rtc_alarm_irq_handler(void)        __attribute__((weak, alias("default_handler")));
void otg_fs_wkup_irq_handler(void)      __attribute__((weak, alias("default_handler")));
void tim8_brk_tim12_irq_handler(void)   __attribute__((weak, alias("default_handler")));
void tim8_up_tim13_irq_handler(void)    __attribute__((weak, alias("default_handler")));
void tim8_trg_com_tim14_irq_handler(void) __attribute__((weak, alias("default_handler")));
void tim8_cc_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void dma1_stream7_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void fsmc_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void sdio_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void tim5_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void spi3_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void uart4_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void uart5_irq_handler(void)            __attribute__((weak, alias("default_handler")));
void tim6_dac_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void tim7_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void dma2_stream0_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma2_stream1_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma2_stream2_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma2_stream3_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma2_stream4_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void eth_irq_handler(void)              __attribute__((weak, alias("default_handler")));
void eth_wkup_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void can2_tx_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void can2_rx0_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void can2_rx1_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void can2_sce_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void otg_fs_irq_handler(void)           __attribute__((weak, alias("default_handler")));
void dma2_stream5_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma2_stream6_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void dma2_stream7_irq_handler(void)     __attribute__((weak, alias("default_handler")));
void usart6_irq_handler(void)           __attribute__((weak, alias("default_handler")));
void i2c3_ev_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void i2c3_er_irq_handler(void)          __attribute__((weak, alias("default_handler")));
void otg_hs_ep1_out_irq_handler(void)   __attribute__((weak, alias("default_handler")));
void otg_hs_ep1_in_irq_handler(void)    __attribute__((weak, alias("default_handler")));
void otg_hs_wkup_irq_handler(void)      __attribute__((weak, alias("default_handler")));
void otg_hs_irq_handler(void)           __attribute__((weak, alias("default_handler")));
void dcmi_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void cryp_irq_handler(void)             __attribute__((weak, alias("default_handler")));
void hash_rng_irq_handler(void)         __attribute__((weak, alias("default_handler")));
void fpu_irq_handler(void)              __attribute__((weak, alias("default_handler")));
