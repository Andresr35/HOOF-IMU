#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>

#define SLEEP_TIME 3000
#define GPS_RECEIVE_BUFF_SIZE 1028
#define RECEIVE_TIMEOUT 100

typedef struct gga
{
    char utcTime[11];        // hhmmss.sss
    char latitude[10];       // ddmm.mmmm
    char nsIndicator;        // N/S
    char longitude[11];      // dddmm.mmmm
    char ewIndicator;        // E/W
    char positionIndicator;  // 0: no fix, 1:GPS fix, 2: Differential GPS fix
    char numOfSatellites[3]; // 0-14
    char hdop[4];
    char *mslAltitude;
    char altitudeUnits;
    char *geoidalSeparation;
    char geoidalUnits;
    int age;
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

#endif