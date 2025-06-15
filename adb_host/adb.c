#include "adb.h"
#include "pio_usb.h"

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
