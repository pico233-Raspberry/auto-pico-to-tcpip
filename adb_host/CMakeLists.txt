cmake_minimum_required(VERSION 3.12)

# 1. 定义项目（必须在 pico_sdk_init 之前）
project(adb_host C CXX ASM)

# 2. 动态定位 Pico SDK
include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/external/pico_sdk_import.cmake)

# 3. 初始化 SDK
pico_sdk_init()

# 4. 添加 PIO-USB 子模块
add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB 
    ${CMAKE_BINARY_DIR}/lib/pico_pio_usb
)

# 5. 可执行文件
add_executable(adb_host
    main.c
    adb.c
)

# 6. 包含头文件路径
target_include_directories(adb_host PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../Pico-PIO-USB/src
)

# 7. 链接库
target_link_libraries(adb_host
    pico_stdlib
    pico_pio_usb_host
)

# 8. 生成 UF2 等输出
pico_add_extra_outputs(adb_host)
