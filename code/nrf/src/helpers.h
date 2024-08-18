#ifndef HELPERS_H
#define HELPERS_H

#include "gps.h"
#include <zephyr/sys/printk.h>
#include "imu.h"
// #include "main.h"

void printGGA(gga gpsData);
void printIMU(gyro gyro, accel accel, int16_t temp);

#endif