// main.c 和 adb.c 的顶部修改为：
#include <stdint.h>      // 添加标准类型定义
#include "pio_usb.h"     // 修改为直接包含 PIO-USB 的头文件
#include "pico/stdlib.h"
#include "adb.h"

int main() {
    // 初始化 USB 主机配置
    pio_usb_configuration_t cfg = PIO_USB_DEFAULT_CONFIG;
    cfg.pin_dp = 2;  // 根据实际硬件连接修改引脚号（例如 GPIO2）

    usb_device_t *host = pio_usb_host_init(&cfg);

    adb_init();

    while (1) {
        if (adb_device_connected()) {
            printf("Device connected! Enabling TCP/IP mode...\n");
            adb_enable_tcpip();
            sleep_ms(5000);
        }
        sleep_ms(100);
    }
}
