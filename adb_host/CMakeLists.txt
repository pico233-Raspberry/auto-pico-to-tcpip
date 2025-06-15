cmake_minimum_required(VERSION 3.12)

# 裸机交叉编译配置
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 强制使用ARM工具链
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# 项目定义
project(adb_host C CXX ASM)

# 包含Pico SDK
include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/external/pico_sdk_import.cmake)
pico_sdk_init()

# 添加PIO-USB子模块
add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB
    ${CMAKE_BINARY_DIR}/lib/pico_pio_usb
)

# 可执行文件
add_executable(adb_host
    main.c
    adb.c
)

# 包含头文件路径
target_include_directories(adb_host PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB/src
    ${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/src/common/pico_stdlib/include
)

# 链接库
target_link_libraries(adb_host
    pico_stdlib
    hardware_pio
    hardware_dma
    pico_pio_usb
    pico_standard_link
)

# 生成UF2等输出
pico_add_extra_outputs(adb_host)
