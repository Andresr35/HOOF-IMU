#include "helpers.h"
#include "math.h"
void printGGA(gga gpsData)
{
    // printk("UTC Time: %s\n", gpsData.utcTime);
    // printk("Latitude: %s\n", gpsData.latitude);
    // printk("%s\t", gpsData.latitude);

    // printk("N/S Indicator: %c\n", gpsData.nsIndicator);
    // printk("Longitude: %s\n", gpsData.longitude);
    // printk("%s\t", gpsData.longitude);

    // printk("E/W Indicator: %c\n", gpsData.ewIndicator);
    // printk("Position Indicator: %c\n", gpsData.positionIndicator);
    // printk("Number of Satellites: %s\n", gpsData.numOfSatellites);
    // printk("HDOP: %s\n", gpsData.hdop);
    // printk("MSL Altitude: %s %c\n", gpsData.mslAltitude, gpsData.altitudeUnits);
    // printk("Geoidal Separation: %s %c\n", gpsData.geoidalSeparation, gpsData.geoidalUnits);
}
void printIMU(gyro gyro, accel accel, int16_t temp)
{
    // printk("Temperature in Fahrenheit : %d F \n", temp);
    // printk("Gyro X is : %d  \n", gyro.x);
    // printk("Gyro Y is : %d  \n", gyro.y);
    // printk("Gyro Z is : %d  \n", gyro.z);
    // printk("\nAccel X is : %d  \t", accel.x);
    // printk("Accel Y is : %d  \t", accel.y);
    // printk("Accel Z is : %d  \t", accel.z);

    // printk("%d\t", temp);
    // printk("%d\t", gyro.x);
    // printk("%d\t", gyro.y);
    // printk("%d\t", gyro.z);
    // printk("%d\t", accel.x);
    // printk("%d\t", accel.y);
    // printk("%d\t", accel.z);
    printAccelDegrees(accel);
}
#define PI 3.14159265358979323846
void printAccelDegrees(accel accel)
{
    // Convert mg to g
    float a_x = accel.x / 1.0;
    float a_y = accel.y / 1.0;
    float a_z = accel.z / 1.0;

    // Calculate pitch (tilt with respect to the X-axis)
    float pitch_radians = atan2((-a_x), sqrt((a_y * a_y) + (a_z * a_z)));

    // Convert radians to degrees
    float pitch_degrees = pitch_radians * (180.0 / PI);
    float roll = atan2(a_y, a_z) * 57.3;
    printk("\nPitch is : %.2f  \t", pitch_degrees * 2);
    printk("Roll is : %.2f ", roll * 2);
}