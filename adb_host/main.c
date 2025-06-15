#include "pico/stdlib.h"
#include "pio_usb.h"
#include "adb.h"

int main() {
    stdio_init_all();
    printf("Pico ADB Host Initializing...\n");

    pio_usb_configuration_t cfg = PIO_USB_DEFAULT_CONFIG;
    cfg.pin_dp = PIO_USB_DP_PIN;
    cfg.pin_dm = PIO_USB_DM_PIN;
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
