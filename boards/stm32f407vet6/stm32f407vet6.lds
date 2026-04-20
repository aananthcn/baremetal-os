/*
 * STM32F407VET6 Linker Script
 *
 * Flash : 0x08000000, 512 kB  (also aliased to 0x00000000 when BOOT0=0)
 * SRAM  : 0x20000000, 128 kB
 * CCM   : 0x10000000,  64 kB  (only CPU-accessible, no DMA)
 */

_OS_STACK_SIZE   = 4096;   /* Main stack (MSP) — used by OS and all ISRs */
_TASK_STACK_SIZE = 4096;   /* Per-task stack pool (PSP) */

MEMORY {
    FLASH  (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
    CCMRAM (rw)  : ORIGIN = 0x10000000, LENGTH = 64K
}

ENTRY(reset_handler)

SECTIONS {

    /* ---- Vector table must be first in Flash ---- */
    .isr_vector : {
        KEEP(*(.isr_vector))
    } > FLASH

    /* ---- Code and read-only data ---- */
    .text : {
        *(.text .text.*)
        *(.rodata .rodata.*)
        *(.glue_7 .glue_7t)
    } > FLASH

    /* ---- Arm stack-unwind tables (needed to avoid random crashes) ---- */
    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH

    /* ---- Initialised data: loaded from Flash, copied to SRAM at startup ---- */
    _init_data_rom = LOADADDR(.data);

    .data : AT (LOADADDR(.data)) {
        _data_start = .;
        *(.data .data.*)
        _data_end = .;
    } > SRAM AT > FLASH

    /* ---- Zero-initialised data ---- */
    .bss (NOLOAD) : {
        _bss_start = .;
        *(.bss .bss.* COMMON)
        _bss_end = .;
    } > SRAM

    /* ---- Stack areas (placed after BSS, growing upward) ---- */
    .stack (NOLOAD) : {
        . = ALIGN(8);
        _task_stack_base = .;
        . = . + _TASK_STACK_SIZE;
        _task_stack_top  = .;

        . = ALIGN(8);
        _os_stack_base   = .;
        . = . + _OS_STACK_SIZE;
        _os_stack_top    = .;   /* Initial MSP — written into vector table slot 0 */
    } > SRAM

    /* Discard C++ exception handling and debug sections */
    /DISCARD/ : {
        *(.eh_frame)
        *(.note.GNU-stack)
    }
}
