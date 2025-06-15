cmake_minimum_required(VERSION 3.12)
cmake_minimum_required(VERSION 3.12)

# 动态定位 SDK（关键修改）
include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/external/pico_sdk_import.cmake)

pico_sdk_init()

project(adb_host)

add_executable(adb_host 
    main.c
)

target_link_libraries(adb_host 
    pico_stdlib
    hardware_pio
)

pico_add_extra_outputs(adb_host)project(adb_host)

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
