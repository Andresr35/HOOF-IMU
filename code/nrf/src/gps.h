#ifndef GPS_H
#define GPS_H
#include "main.h"
#include <zephyr/device.h>


int init_gps(const struct device *gpsUart, gpgps *gps);

#endif