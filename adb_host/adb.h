#pragma once

#include <stdbool.h>

void adb_init();
bool adb_device_connected();
void adb_enable_tcpip();
