cmake_minimum_required(VERSION 3.12)
include(/sdcard/pico/pico-sdk/external/pico_sdk_import.cmake)
project(adb_host)

pico_sdk_init()

add_subdirectory(../../Pico-PIO-USB lib/pico_pio_usb)

add_executable(adb_host
    main.c
    adb.c
)

target_link_libraries(adb_host
    pico_stdlib
    pico_pio_usb_host
)


pico_add_extra_outputs(adb_host)

target_include_directories(adb_host PRIVATE
    ../../Pico-PIO-USB/src
)
