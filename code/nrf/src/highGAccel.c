#include "highGAccel.h"

static const struct i2c_dt_spec highAccelI2C = I2C_DT_SPEC_GET(I2C1_NODE);

int initHighAccel()
{
    int ret;
    if (!device_is_ready(highAccelI2C.bus))
    {
        printk("High G i2c bus %s is not ready!\n\r", highAccelI2C.bus->name);
        return -1;
    }
    // Read from WHOAMI
    uint8_t data = 0;
    uint8_t reg = HighGWHO_AM_I;
    ret = i2c_write_read_dt(&highAccelI2C, &reg, 1, &data, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", highAccelI2C.addr, HighGWHO_AM_I);
        return -1;
    }

    // Setup accel

    // Configure CTRL_REG1: Data rate 50 Hz, normal power mode, enable all axes
    uint8_t config[2] = {HighGCTRL_REG1, 0x27};
    ret = i2c_write_dt(&highAccelI2C, config, sizeof(config));
    if (ret != 0)
    {
        printk("Failed to write to I2C device address %x at Reg. %x \n", highAccelI2C.addr, config[0]);
        return -1;
    }
    // Setup accel
    // Configure CTRL_REG4: medium scale 200g, high-resolution mode
    uint8_t configTwo[2] = {HighGCTRL_REG4, 0x10};
    ret = i2c_write_dt(&highAccelI2C, configTwo, sizeof(configTwo));
    if (ret != 0)
    {
        printk("Failed to write to I2C device address %x at Reg. %x \n", highAccelI2C.addr, configTwo[0]);
        return -1;
    }
    return 1;
}

int readHighAccel(accel *accel)
{
    int ret;
    int8_t accelXLow, accelXHigh;
    uint8_t sensor_regs[2] = {HighGOUT_X_L, HighGOUT_X_H};
    ret = i2c_write_read_dt(&highAccelI2C, &sensor_regs[0], 1, &accelXLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", highAccelI2C.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&highAccelI2C, &sensor_regs[1], 1, &accelXHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", highAccelI2C.addr, WHOAMI);
        return -1;
    }
    accel->x = ((int16_t)(accelXHigh << 8 | accelXLow)) / HIGHACCELSENSITIVITY;

    int8_t accelYLow, accelYHigh;
    uint8_t sensor_regsY[2] = {HighGOUT_Y_L, HighGOUT_Y_H};
    ret = i2c_write_read_dt(&highAccelI2C, &sensor_regsY[0], 1, &accelYLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", highAccelI2C.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&highAccelI2C, &sensor_regsY[1], 1, &accelYHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", highAccelI2C.addr, WHOAMI);
        return -1;
    }
    accel->y = ((int16_t)(accelYHigh << 8 | accelYLow)) / HIGHACCELSENSITIVITY;

    int8_t accelZLow, accelZHigh;
    uint8_t sensor_regsz[2] = {HighGOUT_Z_L, HighGOUT_Z_H};
    ret = i2c_write_read_dt(&highAccelI2C, &sensor_regsz[0], 1, &accelZLow, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", highAccelI2C.addr, WHOAMI);
        return -1;
    }
    ret = i2c_write_read_dt(&highAccelI2C, &sensor_regsz[1], 1, &accelZHigh, 1);
    if (ret != 0)
    {
        printk("Failed to write/read I2C device address %x at Reg. %x \r\n", highAccelI2C.addr, WHOAMI);
        return -1;
    }
    accel->z = ((int16_t)(accelZHigh << 8 | accelZLow)) / HIGHACCELSENSITIVITY;

    // accel->x -= (accel->x % 50);
    // accel->y -= (accel->y % 50);
    // accel->z -= (accel->z % 50);
    return 1;
}
