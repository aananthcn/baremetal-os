add_library(driver_uart STATIC uart.c)

target_include_directories(driver_uart PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/boards
)

target_link_libraries(driver_uart PUBLIC board_${BOARD})
