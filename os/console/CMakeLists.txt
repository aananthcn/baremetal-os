add_library(console STATIC console.c)

target_include_directories(console PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(console PUBLIC driver_uart)
