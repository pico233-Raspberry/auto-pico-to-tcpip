#include "adb.h"
#include "pio_usb.h"

#define ADB_ENDPOINT 0x81

uint32_t usb_host_get_device_count(void) {
    return pio_usb_host_get_device_count();
}

void usb_host_write(uint8_t endpoint, const void* data, uint32_t len) {
    pio_usb_host_endpoint_write(endpoint, data, len);
}

void adb_init() {
    pio_usb_host_init();
}

bool adb_device_connected() {
    return usb_host_get_device_count() > 0;
}

void adb_enable_tcpip() {
    const char* cmd1 = "host:transport:any";
    const char* cmd2 = "shell:setprop service.adb.tcp.port 5555 && stop adbd && start adbd";
    
    uint32_t len = strlen(cmd1);
    uint8_t header[4] = { (len>>24)&0xFF, (len>>16)&0xFF, (len>>8)&0xFF, len&0xFF };
    usb_host_write(ADB_ENDPOINT, header, 4);
    usb_host_write(ADB_ENDPOINT, (uint8_t*)cmd1, len);
    
    len = strlen(cmd2);
    header[0] = (len>>24)&0xFF; header[1] = (len>>16)&0xFF;
    header[2] = (len>>8)&0xFF;  header[3] = len&0xFF;
    usb_host_write(ADB_ENDPOINT, header, 4);
    usb_host_write(ADB_ENDPOINT, (uint8_t*)cmd2, len);
}
