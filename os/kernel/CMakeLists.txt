add_library(kernel STATIC kernel.c)

target_link_libraries(kernel PUBLIC board_${BOARD})
