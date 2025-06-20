#include <stdio.h>
#include "pio_usb.h"
#include "pico/stdlib.h"
#include "adb.h"

int main() {
    stdio_init_all();
    printf("Pico ADB Host Initializing...\n");
    pio_usb_configuration_t cfg = PIO_USB_DEFAULT_CONFIG;
    cfg.pin_dp = 2;
    usb_device_t *host = pio_usb_host_init(&cfg);
    if (!host) {
        printf("USB Host initialization failed!\n");
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
