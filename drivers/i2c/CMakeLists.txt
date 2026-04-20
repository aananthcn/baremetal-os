add_library(driver_i2c STATIC i2c.c)

target_link_libraries(driver_i2c PUBLIC board_${BOARD})
