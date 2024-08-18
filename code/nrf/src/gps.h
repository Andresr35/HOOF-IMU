#ifndef GPS_H
#define GPS_H

// #include "main.h"
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <stdlib.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define RECEIVE_TIMEOUT 100
#define GPS_RECEIVE_BUFF_SIZE 1028

typedef struct gga
{
    char utcTime[11];        // hhmmss.sss
    char latitude[10];       // ddmm.mmmm
    char nsIndicator;        // N/S
    char longitude[11];      // dddmm.mmmm
    char ewIndicator;        // E/W
    char positionIndicator;  // 0: no fix, 1:GPS fix, 2: Differential GPS fix
    char numOfSatellites[3]; // 0-14
    char hdop[5];
    char mslAltitude[5];
    char altitudeUnits;
    char geoidalSeparation[6];
    char geoidalUnits;
} gga;

typedef struct rmc
{
    char *utcTime;
    char status;
    char *latitude;
    char nsIndicator;
    char *longitude;
    char ewIndicator;
    char *speedOverGround;
    char *courseOverGround;
    char *date;
} rmc;

typedef struct gpgps
{
    gga gpgga;
    rmc gprmc;
} gpgps;

int init_gps(gpgps *gps);

#endif