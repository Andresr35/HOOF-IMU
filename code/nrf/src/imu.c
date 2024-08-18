
#include "imu.h"

static const struct i2c_dt_spec imu = I2C_DT_SPEC_GET(I2C0_NODE);

int initIMU()
{
    if (!device_is_ready(imu.bus))
    {
        printk("I2C bus %s is not ready!\n\r", imu.bus->name);
        return -1;
    }
    int ret;
    // Read from WHOAMI
    uint8_t data = 0;
    uint8_t reg = WHOAMI;
    ret = i2c_write_read_dt(&imu, &reg, 1, &data, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    else if (data != 0x6B)
    {
        printk("IMU not found\n");
        return -1;
    }

    // Setup accel
    uint8_t config[2] = {CTRL1XL, 0x40};
    ret = i2c_write_dt(&imu, config, sizeof(config));
    if (ret != 0)
    {
        printk("Failed to write to I2C device address %x at Reg. %x \n", imu.addr, config[0]);
        return -1;
    }

    // Setup gyro
    //  200dps
    uint8_t gconfig[2] = {CTRL2G, 0x60};
    ret = i2c_write_dt(&imu, gconfig, sizeof(gconfig));
    if (ret != 0)
    {
        printk("Failed to write to I2C device address %x at Reg. %x \n", imu.addr, gconfig[0]);
        return -1;
    }
    uint8_t testconfig[2] = {CTRL5C, 0x40};
    ret = i2c_write_dt(&imu, testconfig, sizeof(testconfig));
    if (ret != 0)
    {
        printk("Failed to write to I2C device address %x at Reg. %x \n", imu.addr, testconfig[0]);
        return -1;
    }
    return 1;
}

int readAccel(accel *accel)
{
    int ret;
    u_int16_t accelXLow, accelXHigh;
    uint8_t sensor_regs[2] = {OUTXLA, OUTXHA};
    ret = i2c_write_read_dt(&imu, &sensor_regs[0], 1, &accelXLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&imu, &sensor_regs[1], 1, &accelXHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    accel->x = ((int16_t)(accelXHigh << 8 | accelXLow)) / ACCELSENSITIVITY;

    u_int16_t accelYLow, accelYHigh;
    uint8_t sensor_regsY[2] = {OUTYLA, OUTYHA};
    ret = i2c_write_read_dt(&imu, &sensor_regsY[0], 1, &accelYLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&imu, &sensor_regsY[1], 1, &accelYHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    accel->y = ((int16_t)(accelYHigh << 8 | accelYLow)) / ACCELSENSITIVITY;

    u_int16_t accelZLow, accelZHigh;
    uint8_t sensor_regsz[2] = {OUTZLA, OUTZHA};
    ret = i2c_write_read_dt(&imu, &sensor_regsz[0], 1, &accelZLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&imu, &sensor_regsz[1], 1, &accelZHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    accel->z = ((int16_t)(accelZHigh << 8 | accelZLow)) / ACCELSENSITIVITY;

    accel->x -= (accel->x % 50);
    accel->y -= (accel->y % 50);
    accel->z -= (accel->z % 50);
    return 1;
}

int readGyro(gyro *gyro)
{
    int ret;
    u_int16_t gyroXLow, gyroXHigh;
    uint8_t sensor_regs[2] = {OUTXLG, OUTXHG};
    ret = i2c_write_read_dt(&imu, &sensor_regs[0], 1, &gyroXLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&imu, &sensor_regs[1], 1, &gyroXHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    gyro->x = ((int16_t)(gyroXHigh << 8 | gyroXLow)) / GYROSENSITIVITY;

    u_int16_t gyroYLow, gyroYHigh;
    uint8_t sensor_regsY[2] = {OUTYLG, OUTYHG};
    ret = i2c_write_read_dt(&imu, &sensor_regsY[0], 1, &gyroYLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&imu, &sensor_regsY[1], 1, &gyroYHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    gyro->y = ((int16_t)(gyroYHigh << 8 | gyroYLow)) / GYROSENSITIVITY;

    u_int16_t gyroZLow, gyroZHigh;
    uint8_t sensor_regsz[2] = {OUTZLG, OUTZHG};
    ret = i2c_write_read_dt(&imu, &sensor_regsz[0], 1, &gyroZLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&imu, &sensor_regsz[1], 1, &gyroZHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", imu.addr, WHOAMI);
        return -1;
    }
    gyro->z = ((int16_t)(gyroZHigh << 8 | gyroZLow)) / GYROSENSITIVITY;

    gyro->x -= (gyro->x % 10);
    gyro->y -= (gyro->y % 10);
    gyro->z -= (gyro->z % 10);
    return 1;
}
