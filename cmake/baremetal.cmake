# Helper: add_baremetal_app(name SOURCES ... DRIVERS ...)
#
# Creates a standalone ELF for a single application.
# No two apps are ever linked together.
# Post-build: generates .bin for J-Link/Lauterbach flashing and prints size.

function(add_baremetal_app APP_NAME)
    cmake_parse_arguments(ARG "" "" "SOURCES;DRIVERS" ${ARGN})

    add_executable(${APP_NAME} ${ARG_SOURCES})

    target_include_directories(${APP_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/boards
    )

    target_link_libraries(${APP_NAME} PRIVATE
        bsp_${BOARD}
        board_${BOARD}
        ${ARG_DRIVERS}
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
