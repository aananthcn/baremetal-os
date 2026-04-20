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
 * Symbols provided by the linker script.
 * The extern uint32_t trick gives us the address of each symbol directly;
 * we never dereference them as single values.
 */
extern uint32_t _init_data_rom;    /* Flash LMA of .data section */
extern uint32_t _data_start;       /* SRAM start of .data */
extern uint32_t _data_end;         /* SRAM end of .data */
extern uint32_t _bss_start;        /* SRAM start of .bss */
extern uint32_t _bss_end;          /* SRAM end of .bss */


/* Provided by board.c and each application */
void board_init(void);
int  main(void);


void reset_handler(void) {
    /* Copy initialised data from Flash to SRAM */
    uint32_t *src = &_init_data_rom;
    uint32_t *dst = &_data_start;
    while (dst < &_data_end) {
        *dst++ = *src++;
    }

    /* Zero uninitialised (BSS) data */
    dst = &_bss_start;
    while (dst < &_bss_end) {
        *dst++ = 0;
    }

    /* Board-level hardware init (clocks, flash latency) */
    board_init();

    /* Hand off to the application */
    main();

    /* Should never reach here */
    for (;;);
}
