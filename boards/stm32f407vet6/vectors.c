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

#include <stdint.h>

/*
 * Cortex-M4 vector table for STM32F407VET6.
 *
 * Slot 0  : initial Main Stack Pointer (MSP) — a data value, not a function.
 * Slot 1  : Reset handler.
 * Slots 2–15  : Cortex-M4 processor exceptions.
 * Slots 16–97 : STM32F407 external IRQs 0–81 (RM0090 Table 61).
 *
 * All handlers are declared weak in vector_handlers.c.
 * Override any of them in your application or driver with a strong definition.
 */

/* Linker-script symbol — its address is the initial stack pointer value */
extern uint32_t _os_stack_top;

/* ---- Processor exception handlers ---- */
void reset_handler(void);
void nmi_handler(void);
void hardfault_handler(void);
void memmanage_handler(void);
void busfault_handler(void);
void usagefault_handler(void);
void svcall_handler(void);
void debugmon_handler(void);
void pendsv_handler(void);
void systick_handler(void);

/* ---- External IRQ handlers ---- */
void wwdg_irq_handler(void);
void pvd_irq_handler(void);
void tamp_stamp_irq_handler(void);
void rtc_wkup_irq_handler(void);
void flash_irq_handler(void);
void rcc_irq_handler(void);
void exti0_irq_handler(void);
void exti1_irq_handler(void);
void exti2_irq_handler(void);
void exti3_irq_handler(void);
void exti4_irq_handler(void);
void dma1_stream0_irq_handler(void);
void dma1_stream1_irq_handler(void);
void dma1_stream2_irq_handler(void);
void dma1_stream3_irq_handler(void);
void dma1_stream4_irq_handler(void);
void dma1_stream5_irq_handler(void);
void dma1_stream6_irq_handler(void);
void adc_irq_handler(void);
void can1_tx_irq_handler(void);
void can1_rx0_irq_handler(void);
void can1_rx1_irq_handler(void);
void can1_sce_irq_handler(void);
void exti9_5_irq_handler(void);
void tim1_brk_tim9_irq_handler(void);
void tim1_up_tim10_irq_handler(void);
void tim1_trg_com_tim11_irq_handler(void);
void tim1_cc_irq_handler(void);
void tim2_irq_handler(void);
void tim3_irq_handler(void);
void tim4_irq_handler(void);
void i2c1_ev_irq_handler(void);
void i2c1_er_irq_handler(void);
void i2c2_ev_irq_handler(void);
void i2c2_er_irq_handler(void);
void spi1_irq_handler(void);
void spi2_irq_handler(void);
void usart1_irq_handler(void);
void usart2_irq_handler(void);
void usart3_irq_handler(void);
void exti15_10_irq_handler(void);
void rtc_alarm_irq_handler(void);
void otg_fs_wkup_irq_handler(void);
void tim8_brk_tim12_irq_handler(void);
void tim8_up_tim13_irq_handler(void);
void tim8_trg_com_tim14_irq_handler(void);
void tim8_cc_irq_handler(void);
void dma1_stream7_irq_handler(void);
void fsmc_irq_handler(void);
void sdio_irq_handler(void);
void tim5_irq_handler(void);
void spi3_irq_handler(void);
void uart4_irq_handler(void);
void uart5_irq_handler(void);
void tim6_dac_irq_handler(void);
void tim7_irq_handler(void);
void dma2_stream0_irq_handler(void);
void dma2_stream1_irq_handler(void);
void dma2_stream2_irq_handler(void);
void dma2_stream3_irq_handler(void);
void dma2_stream4_irq_handler(void);
void eth_irq_handler(void);
void eth_wkup_irq_handler(void);
void can2_tx_irq_handler(void);
void can2_rx0_irq_handler(void);
void can2_rx1_irq_handler(void);
void can2_sce_irq_handler(void);
void otg_fs_irq_handler(void);
void dma2_stream5_irq_handler(void);
void dma2_stream6_irq_handler(void);
void dma2_stream7_irq_handler(void);
void usart6_irq_handler(void);
void i2c3_ev_irq_handler(void);
void i2c3_er_irq_handler(void);
void otg_hs_ep1_out_irq_handler(void);
void otg_hs_ep1_in_irq_handler(void);
void otg_hs_wkup_irq_handler(void);
void otg_hs_irq_handler(void);
void dcmi_irq_handler(void);
void cryp_irq_handler(void);
void hash_rng_irq_handler(void);
void fpu_irq_handler(void);


typedef void (*handler_t)(void);

__attribute__((section(".isr_vector"), used))
const handler_t vector_table[] = {
    /* Slot  0 : initial MSP (cast from data pointer — required by hardware) */
    (handler_t) &_os_stack_top,

    /* Slot  1 : Reset */                   reset_handler,
    /* Slot  2 : NMI */                     nmi_handler,
    /* Slot  3 : HardFault */               hardfault_handler,
    /* Slot  4 : MemManage */               memmanage_handler,
    /* Slot  5 : BusFault */                busfault_handler,
    /* Slot  6 : UsageFault */              usagefault_handler,
    /* Slots 7-10 : Reserved */             0, 0, 0, 0,
    /* Slot 11 : SVCall */                  svcall_handler,
    /* Slot 12 : DebugMon */                debugmon_handler,
    /* Slot 13 : Reserved */                0,
    /* Slot 14 : PendSV */                  pendsv_handler,
    /* Slot 15 : SysTick */                 systick_handler,

    /* External IRQs (IRQ0 = slot 16) */
    wwdg_irq_handler,               /* IRQ  0 */
    pvd_irq_handler,                /* IRQ  1 */
    tamp_stamp_irq_handler,         /* IRQ  2 */
    rtc_wkup_irq_handler,           /* IRQ  3 */
    flash_irq_handler,              /* IRQ  4 */
    rcc_irq_handler,                /* IRQ  5 */
    exti0_irq_handler,              /* IRQ  6 */
    exti1_irq_handler,              /* IRQ  7 */
    exti2_irq_handler,              /* IRQ  8 */
    exti3_irq_handler,              /* IRQ  9 */
    exti4_irq_handler,              /* IRQ 10 */
    dma1_stream0_irq_handler,       /* IRQ 11 */
    dma1_stream1_irq_handler,       /* IRQ 12 */
    dma1_stream2_irq_handler,       /* IRQ 13 */
    dma1_stream3_irq_handler,       /* IRQ 14 */
    dma1_stream4_irq_handler,       /* IRQ 15 */
    dma1_stream5_irq_handler,       /* IRQ 16 */
    dma1_stream6_irq_handler,       /* IRQ 17 */
    adc_irq_handler,                /* IRQ 18 */
    can1_tx_irq_handler,            /* IRQ 19 */
    can1_rx0_irq_handler,           /* IRQ 20 */
    can1_rx1_irq_handler,           /* IRQ 21 */
    can1_sce_irq_handler,           /* IRQ 22 */
    exti9_5_irq_handler,            /* IRQ 23 */
    tim1_brk_tim9_irq_handler,      /* IRQ 24 */
    tim1_up_tim10_irq_handler,      /* IRQ 25 */
    tim1_trg_com_tim11_irq_handler, /* IRQ 26 */
    tim1_cc_irq_handler,            /* IRQ 27 */
    tim2_irq_handler,               /* IRQ 28 */
    tim3_irq_handler,               /* IRQ 29 */
    tim4_irq_handler,               /* IRQ 30 */
    i2c1_ev_irq_handler,            /* IRQ 31 */
    i2c1_er_irq_handler,            /* IRQ 32 */
    i2c2_ev_irq_handler,            /* IRQ 33 */
    i2c2_er_irq_handler,            /* IRQ 34 */
    spi1_irq_handler,               /* IRQ 35 */
    spi2_irq_handler,               /* IRQ 36 */
    usart1_irq_handler,             /* IRQ 37 */
    usart2_irq_handler,             /* IRQ 38 */
    usart3_irq_handler,             /* IRQ 39 */
    exti15_10_irq_handler,          /* IRQ 40 */
    rtc_alarm_irq_handler,          /* IRQ 41 */
    otg_fs_wkup_irq_handler,        /* IRQ 42 */
    tim8_brk_tim12_irq_handler,     /* IRQ 43 */
    tim8_up_tim13_irq_handler,      /* IRQ 44 */
    tim8_trg_com_tim14_irq_handler, /* IRQ 45 */
    tim8_cc_irq_handler,            /* IRQ 46 */
    dma1_stream7_irq_handler,       /* IRQ 47 */
    fsmc_irq_handler,               /* IRQ 48 */
    sdio_irq_handler,               /* IRQ 49 */
    tim5_irq_handler,               /* IRQ 50 */
    spi3_irq_handler,               /* IRQ 51 */
    uart4_irq_handler,              /* IRQ 52 */
    uart5_irq_handler,              /* IRQ 53 */
    tim6_dac_irq_handler,           /* IRQ 54 */
    tim7_irq_handler,               /* IRQ 55 */
    dma2_stream0_irq_handler,       /* IRQ 56 */
    dma2_stream1_irq_handler,       /* IRQ 57 */
    dma2_stream2_irq_handler,       /* IRQ 58 */
    dma2_stream3_irq_handler,       /* IRQ 59 */
    dma2_stream4_irq_handler,       /* IRQ 60 */
    eth_irq_handler,                /* IRQ 61 */
    eth_wkup_irq_handler,           /* IRQ 62 */
    can2_tx_irq_handler,            /* IRQ 63 */
    can2_rx0_irq_handler,           /* IRQ 64 */
    can2_rx1_irq_handler,           /* IRQ 65 */
    can2_sce_irq_handler,           /* IRQ 66 */
    otg_fs_irq_handler,             /* IRQ 67 */
    dma2_stream5_irq_handler,       /* IRQ 68 */
    dma2_stream6_irq_handler,       /* IRQ 69 */
    dma2_stream7_irq_handler,       /* IRQ 70 */
    usart6_irq_handler,             /* IRQ 71 */
    i2c3_ev_irq_handler,            /* IRQ 72 */
    i2c3_er_irq_handler,            /* IRQ 73 */
    otg_hs_ep1_out_irq_handler,     /* IRQ 74 */
    otg_hs_ep1_in_irq_handler,      /* IRQ 75 */
    otg_hs_wkup_irq_handler,        /* IRQ 76 */
    otg_hs_irq_handler,             /* IRQ 77 */
    dcmi_irq_handler,               /* IRQ 78 */
    cryp_irq_handler,               /* IRQ 79 */
    hash_rng_irq_handler,           /* IRQ 80 */
    fpu_irq_handler,                /* IRQ 81 */
};
