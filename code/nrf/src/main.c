#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include <unistd.h>
#include <stdlib.h>

#include "main.h"
#include "helpers.h"
#include "gps.h"

const struct device *gpsUart = DEVICE_DT_GET(DT_NODELABEL(uart1));

gpgps gps;

static bool using_buf1 = true;

int main(void)
{
        printk("\nStarting application!\r\n");
        int ret = init_gps(gpsUart, &gps);
        if (ret == -1)
                return 1;
        while (1)
        {
                k_msleep(SLEEP_TIME);
                printk("Working\n");
                printGGA(gps.gpgga);
        }

        return 0;
}
