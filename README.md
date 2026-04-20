# Bare Metal OS — BMOS

An tiny RTOS written by a father, to teach his son, on tiny Embedded System development after knowing that his Proptham too is in the line of Embedded Systems development. I wish he learns from here and grow up, developing advanced systems and concepts that helps humanity to live peacefully and start seeking who they are actually!


# Repository Structure

```
baremetal-os/
├── applications/          # Standalone apps — one binary per app, never linked together
│   ├── led-control/       # Blink PA5 using the GPIO driver
│   └── i2c-slave/         # Receive data as an I2C slave on I2C1
├── boards/
│   └── stm32f407vet6/
│       ├── stm32f407vet6.h    # Peripheral register structs and base addresses
│       ├── stm32f407vet6.lds  # Linker script (Flash at 0x08000000, RAM at 0x20000000)
│       ├── board.c            # Clock init (168 MHz PLL) and SysTick config
│       ├── startup.c          # reset_handler: copy .data, zero .bss, call main()
│       ├── vectors.c          # Cortex-M4 vector table (.isr_vector section)
│       └── vector_handlers.c  # Weak default handlers for all 82 IRQs
├── cmake/
│   ├── arm-none-eabi.cmake    # CMake toolchain file for arm-none-eabi-gcc
│   └── baremetal.cmake        # add_baremetal_app() helper function
├── drivers/
│   ├── gpio/              # gpio.h / gpio.c — clock enable, pin mode, BSRR write
│   └── i2c/               # i2c.h / i2c.c — master and slave polling API
└── os/
    └── kernel/            # kernel.h / kernel.c — kernel_init() / kernel_start() stubs
```


# Getting Started

## Prerequisites

### Linux

Install the ARM bare-metal toolchain and CMake:

```bash
# Ubuntu / Debian
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi cmake ninja-build

# Fedora / RHEL
sudo dnf install arm-none-eabi-gcc-cs arm-none-eabi-binutils-cs cmake ninja-build

# Arch
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils cmake ninja
```

Verify the toolchain is visible:

```bash
arm-none-eabi-gcc --version
```

### macOS

```bash
brew install --cask gcc-arm-embedded
brew install cmake ninja
```

### Windows

Download and install the [Arm GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) and [CMake](https://cmake.org/download/). Add both to `PATH`.


## Build

Configure and build all applications in one step:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

To build only a specific application:

```bash
cmake --build build --target led-control
```

Each application produces three artifacts under `build/applications/<app-name>/`:

| File | Description |
|------|-------------|
| `<app>.elf` | ELF with debug symbols — use with GDB |
| `<app>.bin` | Flat binary for J-Link / Lauterbach download |
| `<app>.hex` | Intel HEX for J-Link / Lauterbach download |

Print the section sizes:

```bash
arm-none-eabi-size build/applications/led-control/led-control.elf
```


## Flash using Segger J-Link

Connect the J-Link probe to the SWD header (SWDIO, SWDCLK, GND, 3.3 V) on the STM32F407VET6 board.

### Command-line (JLinkExe)

```
JLinkExe -device STM32F407VE -if SWD -speed 4000 -autoconnect 1
J-Link> loadbin build/applications/led-control/led-control.bin 0x08000000
J-Link> r
J-Link> g
J-Link> exit
```

Or use the HEX file (address is embedded):

```
J-Link> loadfile build/applications/led-control/led-control.hex
```

### Ozone (Segger graphical debugger)

1. File → New Project Wizard
2. Target device: `STM32F407VE`, Interface: SWD
3. Program file: `build/applications/led-control/led-control.elf`
4. Click **Download & Reset Program**


## Debug using Segger

### GDB + J-Link GDB Server

Open two terminals:

**Terminal 1 — start the GDB server:**

```bash
JLinkGDBServer -device STM32F407VE -if SWD -speed 4000 -port 2331
```

**Terminal 2 — connect GDB:**

```bash
arm-none-eabi-gdb build/applications/led-control/led-control.elf
(gdb) target remote :2331
(gdb) monitor reset
(gdb) load
(gdb) break main
(gdb) continue
```

### Ozone

Open the `.elf` file in Ozone (see Flash section above). Set breakpoints by clicking in the source gutter and press **F5** to run.


## Flash and Debug using Lauterbach TRACE32

Connect the TRACE32 debug cable to the SWD/JTAG header.

**Flash script (`flash.cmm`):**

```
SYStem.CPU STM32F407VE
SYStem.CONFIG.DEBUGPORTTYPE SWD
SYStem.Up
Data.LOAD.Elf "build/applications/led-control/led-control.elf"
Go
ENDDO
```

Run from TRACE32 PowerView: `DO flash.cmm`

**Debug session:**

```
SYStem.CPU STM32F407VE
SYStem.CONFIG.DEBUGPORTTYPE SWD
SYStem.Up
Data.LOAD.Elf "build/applications/led-control/led-control.elf" /NoClear
Break.Set main
Go
ENDDO
```


# Adding a New Application

1. Create the directory and source file:

```bash
mkdir applications/my-app
touch applications/my-app/main.c
```

2. Write `main.c`:

```c
#include <os/kernel/kernel.h>

int main(void) {
    kernel_init();
    /* your application code */
    kernel_start();
    for (;;);
}
```

3. Add `applications/my-app/CMakeLists.txt`:

```cmake
add_baremetal_app(my-app
    SOURCES main.c
    DRIVERS driver_gpio   # list any drivers you need
)
```

4. Register the new app in `applications/CMakeLists.txt`:

```cmake
add_subdirectory(my-app)
```

5. Rebuild:

```bash
cmake --build build --target my-app
```

The resulting `my-app.bin` and `my-app.elf` will appear under `build/applications/my-app/`.


# Target Hardware

| Resource | Address / Value |
|----------|----------------|
| Flash    | 0x08000000, 512 kB |
| SRAM     | 0x20000000, 128 kB |
| CCM RAM  | 0x10000000, 64 kB |
| RCC      | 0x40023800 |
| GPIOA    | 0x40020000 |
| USART1   | 0x40011000 |
| I2C1     | 0x40005400 |
| TIM2     | 0x40000000 |
| SysTick  | 0xE000E010 |

Default clock after `board_init()`: **168 MHz** (HSI → PLL, 5 Flash wait states, APB1 ÷4, APB2 ÷2).


# Architecture Notes

- **One binary per application** — no two apps are ever linked together.
- **No dynamic allocation** — stack sizes are fixed in the linker script via `_TASK_STACK_SIZE` and `_OS_STACK_SIZE`.
- **No stdlib** — only `libgcc` is linked for compiler builtins. No `printf`, `malloc`, or `memcpy` from libc.
- **Cooperative scheduler** — `kernel_start()` is a stub today; tasks will yield voluntarily when implemented. SysTick is used for tick counting only, not forced context switches.
- **Weak IRQ handlers** — every interrupt has a default infinite-loop handler. Override any handler by defining a function with the same name in your application (e.g., `void tim2_irq_handler(void) { ... }`).
