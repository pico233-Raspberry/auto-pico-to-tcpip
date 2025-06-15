
#include <stdio.h>
#include "pico/pio_usb.h"  // 包含USB配置结构体
#include "pico/stdlib.h"
#include "pio_usb.h"
#include "adb.h"

int main() {
    stdio_init_all();
    printf("Pico ADB Host Initializing...\n");

    pio_usb_configuration_t cfg = PIO_USB_DEFAULT_CONFIG;
    cfg.pin_dp = 2;  // 根据实际硬件连接修改引脚号
usb_device_t *host = pio_usb_host_init(&cfg);  // 注意类型改为 usb_device_t
    usb_host_t *host = pio_usb_host_init(&cfg);

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
