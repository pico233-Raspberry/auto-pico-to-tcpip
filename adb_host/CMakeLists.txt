cmake_minimum_required(VERSION 3.12)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/../pico-sdk)
set(PICO_PLATFORM "rp2040")
set(PICO_COMPILER pico_arm_gcc)
set(PICO_TOOLCHAIN_PATH /usr/bin)

set(PICO_BUILD_PICOTOOL OFF CACHE BOOL "" FORCE)
set(PICO_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(PICO_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(PICO_NO_HARDWARE ON CACHE BOOL "" FORCE)

project(adb_host C CXX ASM)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init(NO_BOOTSTRAP)

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB
    ${CMAKE_BINARY_DIR}/lib/pico_pio_usb
)

add_executable(adb_host main.c adb.c)
target_include_directories(adb_host PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB/src
    ${PICO_SDK_PATH}/src/common/pico_stdlib/include
)
target_link_libraries(adb_host
    pico_stdlib
    hardware_pio
    hardware_dma
    pico_pio_usb
)
pico_add_extra_outputs(adb_host)
