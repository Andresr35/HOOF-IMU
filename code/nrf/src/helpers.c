#include "helpers.h"
#include "main.h"
#include <zephyr/sys/printk.h>

void printGGA(gga gpsData)
{
    printk("UTC Time: %s\n", gpsData.utcTime);
    printk("Latitude: %s\n", gpsData.latitude);
    printk("N/S Indicator: %c\n", gpsData.nsIndicator);
    printk("Longitude: %s\n", gpsData.longitude);
    printk("E/W Indicator: %c\n", gpsData.ewIndicator);
    printk("Position Indicator: %c\n", gpsData.positionIndicator);
    printk("Number of Satellites: %s\n", gpsData.numOfSatellites);
    printk("HDOP: %s\n", gpsData.hdop);
    printk("MSL Altitude: %s %c\n", gpsData.mslAltitude, gpsData.altitudeUnits);
    printk("Geoidal Separation: %s %c\n", gpsData.geoidalSeparation, gpsData.geoidalUnits);
}