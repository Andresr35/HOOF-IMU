#include "helpers.h"

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
void printIMU(gyro gyro, accel accel, int16_t temp)
{
    printk("Temperature in Fahrenheit : %d F \n", temp);
    printk("Gyro X is : %d  \n", gyro.x);
    printk("Gyro Y is : %d  \n", gyro.y);
    printk("Gyro Z is : %d  \n", gyro.z);
    printk("Accel X is : %d  \n", accel.x);
    printk("Accel Y is : %d  \n", accel.y);
    printk("Accel Z is : %d  \n", accel.z);
}
