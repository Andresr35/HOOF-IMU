#ifndef HIGHGACCEL_H
#define HIGHGACCEL_H
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include "imu.h"
#define I2C1_NODE DT_NODELABEL(highgaccelsensor)

// High g accel
#define HighGWHO_AM_I 0x0F
#define HighGCTRL_REG1 0x20
#define HighGCTRL_REG4 0x23
#define HighGOUT_X_L 0x28
#define HighGOUT_X_H 0x29
#define HighGOUT_Y_L 0x2A
#define HighGOUT_Y_H 0x2B
#define HighGOUT_Z_L 0x2C
#define HighGOUT_Z_H 0x2D
#define HIGHACCELSENSITIVITY 98

int initHighAccel();
int readHighAccel(accel *accel);

#endif