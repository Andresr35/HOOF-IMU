#include "main.h"

gpgps gps;

static const struct i2c_dt_spec magnetometer = I2C_DT_SPEC_GET(I2C0_NODE);

int initMag()
{
        if (!device_is_ready(magnetometer.bus))
        {
                printk("I2C bus %s is not ready!\n\r", magnetometer.bus->name);
                return -1;
        }
        int ret;
        // Read from WHOAMI
        uint8_t data = 0;
        uint8_t reg = WHOAMI;
        ret = i2c_write_read_dt(&magnetometer, &reg, 1, &data, 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        else if (data != 0x30)
        {
                printk("Magnetometer not found\n");
                return -1;
        }
        return 1;
}
int readMag(mag *mag)
{
        // Read X Y and Z values
        int ret;
        uint8_t xValues[3];
        uint8_t xRegs[3] = {MMC5983MA_XOUT0, MMC5983MA_XOUT1, MMC5983MA_XYZOUT2};
        ret = i2c_write_read_dt(&magnetometer, &xRegs[0], 1, &xValues[0], 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        ret = i2c_write_read_dt(&magnetometer, &xRegs[1], 1, &xValues[1], 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        ret = i2c_write_read_dt(&magnetometer, &xRegs[2], 1, &xValues[2], 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        uint8_t yValues[2];
        uint8_t yRegs[2] = {MMC5983MA_YOUT0, MMC5983MA_YOUT1};
        ret = i2c_write_read_dt(&magnetometer, &yRegs[0], 1, &yValues[0], 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        ret = i2c_write_read_dt(&magnetometer, &yRegs[1], 1, &yValues[1], 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        uint8_t zValues[2];
        uint8_t zRegs[2] = {MMC5983MA_ZOUT0, MMC5983MA_ZOUT1};
        ret = i2c_write_read_dt(&magnetometer, &zRegs[0], 1, &zValues[0], 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        ret = i2c_write_read_dt(&magnetometer, &zRegs[1], 1, &zValues[1], 1);
        if (ret != 0)
        {
                printk("Failed to write/read I2C device address %x at Reg. %x \r\n", magnetometer.addr, WHOAMI);
                return -1;
        }
        mag->x = ((xValues[0] << 10) | (xValues[1] << 2) | ((xValues[2] >> 6) & 0x03));
        mag->y = ((yValues[0] << 10) | (yValues[1] << 2) | ((xValues[2] >> 4) & 0x03));
        mag->z = ((zValues[0] << 10) | (zValues[1] << 2) | ((xValues[2] >> 2) & 0x03));
        return 1;
}

int printMag(mag *mag)
{
        printk("X: %ld\t", mag->x);
        printk("Y: %ld\t", mag->y);
        printk("Z: %ld\n", mag->z);
        return 1;
}

float compute_heading(int32_t raw_x, int32_t raw_y)
{
        // Convert raw data to µT
        float Bx = raw_x * SENSITIVITY;
        float By = raw_y * SENSITIVITY;

        // Compute heading using atan2 (radians to degrees)
        float heading = atan2(By, Bx) * (180.0 / PI);

        // Ensure heading is in the range [0, 360)
        if (heading < 0)
        {
                heading += 360.0;
        }

        return heading;
}

int main(void)
{
        printk("\nStarting application!\r\n");
        int ret = init_gps(&gps);
        if (ret == -1)
                return 1;

        ret = initIMU();
        if (ret == -1)
                return 1;
        ret = initHighAccel();
        if (ret == -1)
                return 1;
        ret = initMag();
        if (ret == -1)
                return 1;
        accel highGAccel;
        accel accel;
        gyro gyro;
        mag mag;

        while (1)
        {
                k_msleep(SLEEP_TIME);
                // printk("Working\n");
                readAccel(&accel);
                readGyro(&gyro);
                // printIMU(gyro, accel, getTemp());
                if (readMag(&mag) == -1)
                        return -1;

                if (printMag(&mag) == -1)
                        return -1;
                int32_t heading = compute_heading(mag.x, mag.y);
                printf("Heading: %d degrees\n", heading);
                // readHighAccel(&highGAccel);
                // printk("%d\t", highGAccel.x);
                // printk("%d\t", highGAccel.y);
                // printk("%d\t", highGAccel.z);
                // printGGA(gps.gpgga);
                // printk("\n");
        }

        return 0;
}
