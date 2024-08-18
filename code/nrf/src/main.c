#include "main.h"

gpgps gps;

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
        accel highGAccel;
        accel accel;
        gyro gyro;

        while (1)
        {
                k_msleep(SLEEP_TIME);
                printk("Working\n");
                readAccel(&accel);
                readGyro(&gyro);
                printIMU(gyro, accel, getTemp());
                readHighAccel(&highGAccel);
                printk("high Accel X is : %d  \n", highGAccel.x);
                printk("high Accel Y is : %d  \n", highGAccel.y);
                printk("high Accel Z is : %d  \n", highGAccel.z);
                // printGGA(gps.gpgga);
        }

        return 0;
}
