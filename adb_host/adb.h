#ifndef ADB_H
#define ADB_H

#include <stdbool.h>

void adb_init();
bool adb_device_connected();
void adb_enable_tcpip();

#endif
