// main.c 和 adb.c 的顶部修改为：
#include <stdint.h>      // 添加标准类型定义
#include "pio_usb.h"     // 修改为直接包含 PIO-USB 的头文件
#include "pico/stdlib.h"
#define ADB_ENDPOINT 0x81

static void adb_send_frame(const char* cmd) {
    uint32_t len = strlen(cmd);
    uint8_t header[4] = {
        (len >> 24) & 0xFF, (len >> 16) & 0xFF,
        (len >> 8) & 0xFF, len & 0xFF
    };
    usb_host_write(ADB_ENDPOINT, header, 4);
    usb_host_write(ADB_ENDPOINT, (uint8_t*)cmd, len);
}

void adb_enable_tcpip() {
    adb_send_frame("host:transport:any");
    adb_send_frame("shell:setprop service.adb.tcp.port 5555 && stop adbd && start adbd");
}


bool adb_device_connected() {
    return usb_host_get_device_count() > 0;
}
