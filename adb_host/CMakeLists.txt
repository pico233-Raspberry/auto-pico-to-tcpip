cmake_minimum_required(VERSION 3.12)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(PICO_BUILD_PICOTOOL OFF)

project(adb_host C CXX ASM)

include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/external/pico_sdk_import.cmake)
pico_sdk_init()

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB
    ${CMAKE_BINARY_DIR}/lib/pico_pio_usb
)

add_executable(adb_host
    main.c
    adb.c
)

target_include_directories(adb_host PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB/src
    ${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/src/common/pico_stdlib/include
)

target_link_libraries(adb_host
    pico_stdlib
    hardware_pio
    hardware_dma
    pico_pio_usb
)

pico_add_extra_outputs(adb_host)
