add_library(driver_gpio STATIC gpio.c)

target_link_libraries(driver_gpio PUBLIC board_${BOARD})
