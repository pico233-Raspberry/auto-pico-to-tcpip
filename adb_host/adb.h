#ifndef ADB_H
#define ADB_H
#include <stdbool.h>
#include "pio_usb.h"

uint32_t usb_host_get_device_count(void);
void usb_host_write(uint8_t endpoint, const void* data, uint32_t len);

void adb_init();
bool adb_device_connected();
void adb_enable_tcpip();
#endif
