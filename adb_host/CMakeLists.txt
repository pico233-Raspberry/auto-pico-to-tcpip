cmake_minimum_required(VERSION 3.12)

# 动态定位 Pico SDK
include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/external/pico_sdk_import.cmake)

# 初始化 SDK（只需一次）
pico_sdk_init()

# 项目定义
project(adb_host)

# 添加 PIO-USB 子模块（路径需确认是否正确）
add_subdirectory(../../Pico-PIO-USB lib/pico_pio_usb)

# 可执行文件
add_executable(adb_host
    main.c
    adb.c
)

# 链接库
target_link_libraries(adb_host
    pico_stdlib
    pico_pio_usb_host  # 确保子模块正确导出此库名
)

# 包含头文件路径
target_include_directories(adb_host PRIVATE
    ../../Pico-PIO-USB/src  # 确认路径是否指向实际头文件位置
)

# 生成额外输出（UF2等）
pico_add_extra_outputs(adb_host)
