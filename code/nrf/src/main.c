#include "main.h"

gpgps gps;

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
LOG_MODULE_REGISTER(Lesson2_Exercise1, LOG_LEVEL_INF);

static const struct bt_data ad[] = {
    // advertising flags
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    // advertising packet data
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static unsigned char url_data[] = {0x17, '/', '/', 'a', 'c', 'a', 'd', 'e', 'm', 'y', '.',
                                   'n', 'o', 'r', 'd', 'i', 'c', 's', 'e', 'm', 'i', '.',
                                   'c', 'o', 'm'};

static const struct bt_data sd[] = {
    /* 4.2.3 Include the URL data in the scan response packet*/
    BT_DATA(BT_DATA_URI, url_data, sizeof(url_data)),
};

int main(void)
{
        int blink_status = 0;
        int err;
        bt_addr_le_t addr;
        err = bt_addr_le_from_str("FF:EE:DD:CC:BB:AA", "random", &addr);
        if (err)
        {
                printk("Invalid BT address (err %d)\n", err);
        }

        err = bt_id_create(&addr, NULL);
        if (err < 0)
        {
                printk("Creating new ID failed (err %d)\n", err);
        }

        // static struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM((BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_USE_IDENTITY),
        //                                                            800,   /*Min Advertising Interval 500ms (800*0.625ms) */
        //                                                            801,   /*Max Advertising Interval 500.625ms (801*0.625ms)*/
        //                                                            NULL); /* Set to NULL for undirected advertising*/

        // enable bt
        err = bt_enable(NULL);
        if (err)
        {
                LOG_ERR("Bluetooth init failed (err %d)\n", err);
                return -1;
        }
        LOG_INF("Bluetooth initialized\n");

        // Start advertising
        err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
        if (err)
        {
                LOG_ERR("Advertising failed to start (err %d)\n", err);
                return -1;
        }

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
                readHighAccel(&highGAccel);
                // printIMU(gyro, accel, getTemp());
                // printk("high Accel X is : %d  \n", highGAccel.x);
                // printk("high Accel Y is : %d  \n", highGAccel.y);
                // printk("high Accel Z is : %d  \n", highGAccel.z);
                // printGGA(gps.gpgga);
        }

        return 0;
}
