#include <stdio.h>      // 添加标准IO头文件
#include <stdbool.h>    // 添加bool类型支持
#include "pio_usb.h"    // PIO-USB头文件
#include "pico/stdlib.h"
#include "adb.h"

int main() {
    stdio_init_all();

    // USB主机配置
    pio_usb_configuration_t cfg = PIO_USB_DEFAULT_CONFIG;
    cfg.pin_dp = 2;  // 根据实际硬件连接修改GPIO引脚

    usb_device_t *host = pio_usb_host_init(&cfg);
    if (!host) {
        printf("USB Host init failed!\n");
        return -1;
    }

    adb_init();
    while (true) {
        if (adb_device_connected()) {
            printf("Device connected! Enabling TCP/IP mode...\n");
            adb_enable_tcpip();
        }
        sleep_ms(100);
    }
}
