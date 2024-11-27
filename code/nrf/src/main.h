#ifndef MAIN_H
#define MAIN_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "helpers.h"
#include "gps.h"
#include "imu.h"
#include "highGAccel.h"

#define SLEEP_TIME 200
#define I2C0_NODE DT_NODELABEL(magnetometer)
#define WHOAMI 0x2f
#define MMC5983MA_XOUT0 0x00   // X-axis MSB
#define MMC5983MA_YOUT0 0x02   // Y-axis MSB
#define MMC5983MA_ZOUT0 0x04   // Z-axis MSB
#define MMC5983MA_XOUT1 0x01   // X-axis LSB
#define MMC5983MA_YOUT1 0x03   // Y-axis LSB
#define MMC5983MA_ZOUT1 0x05   // Z-axis LSB
#define MMC5983MA_XYZOUT2 0x06 // Control register 1
#define SENSITIVITY 0.25       // µT/LSB
#define PI 3.14159265358979323846
typedef struct mag
{
    int32_t x;
    int32_t y;
    int32_t z;
} mag;

#endif