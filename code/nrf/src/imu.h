#ifndef IMU_H
#define IMU_H
#include <unistd.h>
#include <zephyr/drivers/i2c.h>

// imu sensor
#define I2C0_NODE DT_NODELABEL(accelsensor)
#define WHOAMI 0X0F
// control reg
#define CTRL1XL 0x10
#define CTRL2G 0x11
#define CTRL5C 0x14
#define STATUSREG 0x1E
// gyro
#define OUTXLG 0x22
#define OUTXHG 0x23
#define OUTYLG 0x24
#define OUTYHG 0x25
#define OUTZLG 0x26
#define OUTZHG 0x27
// accel
#define OUTXLA 0x28
#define OUTXHA 0x29
#define OUTYLA 0x2A
#define OUTYHA 0x2B
#define OUTZLA 0x2C
#define OUTZHA 0x2D
// temp
#define OUTTEMPL 0x20
#define OUTTEMPH 0x21
// sensitivity
#define GYROSENSITIVITY 16.4
//
#define ACCELSENSITIVITY 16

typedef struct accel
{
    int16_t x;
    int16_t y;
    int16_t z;
} accel;
typedef struct gyro
{
    int16_t x;
    int16_t y;
    int16_t z;
} gyro;

// Send contr regs and makes sure it can read imu
int initIMU();
int readAccel(accel *accel);
int readGyro(gyro *gyro);
int16_t getTemp();
#endif