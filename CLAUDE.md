# Baremetal OS

## Project Goal

Develop a baremetal OS for the **STM32F407VET6** board (Cortex-M4, 512kB Flash, 192kB RAM), with support for additional boards added incrementally. The primary audience is **learners** who want to write, flash, and debug standalone embedded applications.

## Repository Structure

```
baremetal-os/
├── applications/          # Standalone apps — one binary per app, never linked together
│   ├── led-control/       # Example: blink PA5 using GPIO driver
│   └── i2c-slave/         # Example: receive data as I2C slave on I2C1
├── boards/
│   └── stm32f407vet6/
│       ├── stm32f407vet6.h    # Peripheral register structs and base addresses
│       ├── stm32f407vet6.lds  # Linker script (Flash at 0x0, RAM at 0x20000000)
│       └── stm32f407vet6.mk   # Compiler/linker flags for arm-none-eabi-gcc
├── drivers/
│   ├── gpio/              # gpio.h / gpio.c — clock enable, pin mode, write
│   └── i2c/               # i2c.h (stub)
└── os/
    └── kernel/            # kernel.c — kernel_init() and kernel_start() stubs
```

## Architecture Rules

- **One binary per application.** No two apps are ever linked together. Each `applications/<name>/` directory builds into its own standalone ELF/binary.
- **OS is non-preemptive.** The scheduler (to be implemented) is cooperative. SysTick or a general-purpose timer interrupt may be used to generate system ticks, but task switching is not forced — tasks yield voluntarily.
- **Infrastructure folders** (`boards/`, `drivers/`, `os/`) provide shared primitives. Apps include what they need; nothing is pulled in automatically.
- **No dynamic allocation.** Stack sizes for user, OS, and IRQ contexts are fixed in the linker script via `_TASK_STACK_SIZE`, `_OS_STACK_SIZE`, and `_IRQ_STACK_SIZE`.

## Toolchain

- Compiler: `arm-none-eabi-gcc` (Cortex-M4, Thumb-2: `-mthumb -march=armv7e-m -mcpu=cortex-m4`)
- Linker: `arm-none-eabi-ld` with board-specific `.lds` and `-nostdlib -lgcc`
- Flash/Debug: **Segger J-Link** or **Lauterbach TRACE32** — no OpenOCD dependency assumed

## Key Hardware Details (STM32F407VET6)

| Resource | Address / Value |
|----------|----------------|
| Flash    | 0x00000000, 512 kB |
| SRAM     | 0x20000000, 128 kB |
| CCM RAM  | 0x10000000, 64 kB |
| RCC      | 0x40023800 |
| GPIOA–C  | 0x40020000, +0x400 each |
| USART1/2 | 0x40011000 / 0x40004400 |
| I2C1     | 0x40005400 |
| TIM2     | 0x40000000 |

Vector table starts at `_vectors_start` (ROM base); entry point is `_vectors_start`.

## Adding a New Application

1. Create `applications/<app-name>/main.c`.
2. Add a `Makefile` or extend the top-level build to compile that directory into its own ELF, linking against the board `.lds` and any required drivers.
3. Flash with J-Link (`JLinkExe`) or Lauterbach (`practice` script) targeting the STM32F407VET6.
4. The app must define its own `main()`. It should call `kernel_init()` then `kernel_start()` if it uses OS services; otherwise it can loop directly.

## Code Conventions

- Peripheral structs use `volatile u32` fields; always access registers through the typed struct macros (`GPIOA->MODER`, `RCC->AHB1ENR`, etc.).
- Driver headers include the board header via `<stm32f407vet6/stm32f407vet6.h>`.
- No stdlib (no `printf`, `malloc`, `memcpy` from libc) — only `libgcc` is linked for compiler builtins.
- Keep files small and single-purpose. No cross-driver dependencies.

## Current Status

The codebase is **intentionally incomplete** — it is a learning scaffold:

- `kernel_init()` and `kernel_start()` are stubs; scheduler not yet implemented.
- GPIO driver is functional (clock enable, output mode, BSRR write).
- I2C driver header exists; implementation is missing.
- No startup `.s` file or `vector_handlers.c` visible yet in the new layout — these are referenced in `stm32f407vet6.mk` and need to be added under `boards/stm32f407vet6/`.
