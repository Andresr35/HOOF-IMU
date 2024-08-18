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
        accel accel;
        gyro gyro;
        while (1)
        {
                k_msleep(SLEEP_TIME);
                printk("Working\n");
                readAccel(&accel);
                readGyro(&gyro);
                printk("Gyro X is : %d  \n", gyro.x);
                printk("Gyro Y is : %d  \n", gyro.y);
                printk("Gyro Z is : %d  \n", gyro.z);
                printk("Accel X is : %d  \n", accel.x);
                printk("Accel Y is : %d  \n", accel.y);
                printk("Accel Z is : %d  \n", accel.z);

                // printGGA(gps.gpgga);
        }

        return 0;
}
