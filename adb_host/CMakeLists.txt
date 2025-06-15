cmake_minimum_required(VERSION 3.12)

# 强制使用 ARM 工具链（关键修复）
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# 定义项目
project(adb_host C CXX ASM)

# 包含 Pico SDK
include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/external/pico_sdk_import.cmake)

# 初始化 SDK（必须在 project() 之后）
pico_sdk_init()

# 添加 PIO-USB 子模块
add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB
    ${CMAKE_BINARY_DIR}/lib/pico_pio_usb
)

# 可执行文件
add_executable(adb_host
    main.c
    adb.c
)

# 链接所有必需的库（关键修改）
target_link_libraries(adb_host
    pico_stdlib
    hardware_pio
    hardware_dma
    pico_pio_usb
)

# 生成 UF2 等输出
pico_add_extra_outputs(adb_host)
