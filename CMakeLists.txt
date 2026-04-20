cmake_minimum_required(VERSION 3.20)

# Must be set before project()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-none-eabi.cmake
    CACHE FILEPATH "Toolchain file")

project(baremetal-os C ASM)

# Board selection — extend this list as new boards are added
set(BOARD stm32f407vet6 CACHE STRING "Target board")
set_property(CACHE BOARD PROPERTY STRINGS stm32f407vet6)

include(cmake/baremetal.cmake)

add_subdirectory(boards/${BOARD})
add_subdirectory(drivers)
add_subdirectory(os)
add_subdirectory(applications)
