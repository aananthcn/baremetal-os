# Helper: add_baremetal_app(name SOURCES ... DRIVERS ... FEATURES ...)
#
# Creates a standalone ELF for a single application.
# No two apps are ever linked together.
# DRIVERS  — hardware driver libraries (e.g. driver_gpio, driver_uart)
# FEATURES — OS-level libraries that are not drivers (e.g. console)
# Post-build: generates .bin for J-Link/Lauterbach flashing and prints size.

function(add_baremetal_app APP_NAME)
    cmake_parse_arguments(ARG "" "" "SOURCES;DRIVERS;FEATURES" ${ARGN})

    add_executable(${APP_NAME} ${ARG_SOURCES})

    set_target_properties(${APP_NAME} PROPERTIES SUFFIX .elf)

    target_include_directories(${APP_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/boards
    )

    target_link_libraries(${APP_NAME} PRIVATE
        bsp_${BOARD}
        board_${BOARD}
        ${ARG_DRIVERS}
        ${ARG_FEATURES}
    )

    # Flat binary for flash download
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary
                $<TARGET_FILE:${APP_NAME}>
                ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex
                $<TARGET_FILE:${APP_NAME}>
                ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.hex
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${APP_NAME}>
        COMMENT "Building ${APP_NAME}.bin / .hex"
    )
endfunction()
