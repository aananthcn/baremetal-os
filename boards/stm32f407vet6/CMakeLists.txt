cmake_minimum_required(VERSION 3.20)

# ---- Interface target: board-specific compile and link flags ----
#
# Every app links against this target to inherit the correct MCU flags
# and linker script without duplicating settings.

add_library(board_stm32f407vet6 INTERFACE)

target_compile_options(board_stm32f407vet6 INTERFACE
    -mthumb
    -mthumb-interwork
    -march=armv7e-m
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -Wall
    -Werror
    -g
    -Os
    -ffunction-sections
    -fdata-sections
    -ffreestanding
)

target_link_options(board_stm32f407vet6 INTERFACE
    -mthumb
    -march=armv7e-m
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -nostdlib
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
    -T ${CMAKE_CURRENT_SOURCE_DIR}/stm32f407vet6.lds
)

target_link_libraries(board_stm32f407vet6 INTERFACE gcc)

target_include_directories(board_stm32f407vet6 INTERFACE
    ${CMAKE_SOURCE_DIR}          # for <drivers/...>, <os/...>
    ${CMAKE_SOURCE_DIR}/boards   # for <stm32f407vet6/stm32f407vet6.h>
)


# ---- BSP object library: startup, vector table, board init ----
#
# Built as OBJECT so its translation units are linked directly into each
# application ELF rather than archived into a static library.
# This ensures the vector table section (.isr_vector) is never stripped.

add_library(bsp_stm32f407vet6 OBJECT
    startup.c
    vectors.c
    vector_handlers.c
    board.c
)

target_link_libraries(bsp_stm32f407vet6 PUBLIC board_stm32f407vet6)
