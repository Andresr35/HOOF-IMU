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

const struct device *gpsUart = DEVICE_DT_GET(DT_NODELABEL(uart1));
static uint8_t gps_rx_next_buf[GPS_RECEIVE_BUFF_SIZE] = {0};
static uint8_t gps_rx_buf[GPS_RECEIVE_BUFF_SIZE] = {0};
gpgps gps;

void parse_nmea(const char *nmea_sentence)
{
        // printk("Running\n");
        // char *sentences = (char *)malloc(GPS_RECEIVE_BUFF_SIZE);

        // strncpy(sentences, nmea_sentence, GPS_RECEIVE_BUFF_SIZE - 1);
        // // printk("Line: %s\n", sentences);
        char *saveptr;
        // // Skip the first one cause its bad
        char *line = strtok_r(nmea_sentence, "\n", &saveptr);
        // // printk("First line is: %s\n", line);

        // // printk("Second line is: %s\n", line);
        // // Looping through each line

        char *id;
        while ((line = strtok_r(NULL, "\n", &saveptr)))
        {
                char *saveIDPointer;
                //         // printk("Line: %s\n", line);

                id = strtok_r(line, ",", &saveIDPointer);
                //         // printk("ID is:%s\n", id);
                //         // // Looping through each id
                if (strcmp(id, "$GPGGA") == 0)
                {
                        // printk("We got some data");
                        int i = 0;
                        while ((id = strtok_r(NULL, ",", &saveIDPointer)))
                        {
                                switch (i)
                                {
                                case 0:
                                        if (strlen(id) == 10)
                                        {
                                                strncpy(gps.gpgga.utcTime, id, 10);
                                                gps.gpgga.utcTime[10] = '\0';
                                        }

                                        break;
                                case 1:
                                        if (strlen(id) == 9)
                                        {
                                                strncpy(gps.gpgga.latitude, id, 9);
                                                gps.gpgga.latitude[9] = '\0';
                                        }
                                        break;
                                case 2:
                                        if (strlen(id) == 1)
                                        {
                                                gps.gpgga.nsIndicator = id[0];
                                        }

                                        break;
                                case 3:
                                        if (strlen(id) == 10)
                                        {
                                                strncpy(gps.gpgga.longitude, id, 10);
                                                gps.gpgga.longitude[10] = '\0';
                                        }
                                        break;
                                case 4:
                                        if (strlen(id) == 1)
                                        {
                                                gps.gpgga.ewIndicator = id[0];
                                        }
                                        break;
                                case 5:
                                        if (strlen(id) == 1)
                                        {
                                                gps.gpgga.positionIndicator = id[0];
                                        }
                                        break;
                                case 6:
                                        if (strlen(id) == 2)
                                        {
                                                strncpy(gps.gpgga.numOfSatellites, id, 2);
                                                gps.gpgga.numOfSatellites[2] = '\0';
                                        }
                                        break;
                                case 7:
                                        if (strlen(id) == 4)
                                        {
                                                strncpy(gps.gpgga.hdop, id, 4);
                                                gps.gpgga.hdop[4] = '\0';
                                        }
                                        break;
                                // case 8:
                                //         gps.gpgga.mslAltitude = strtof(id, NULL);
                                //         break;
                                // case 9:
                                //         gps.gpgga.altitudeUnits = id[0];
                                //         break;
                                // case 10:
                                //         gps.gpgga.geoidalSeparation = strtof(id, NULL);
                                //         break;
                                // case 11:
                                //         gps.gpgga.geoidalUnits = id[0];
                                //         break;
                                // case 12:
                                //         gps.gpgga.age = (int)strtol(id, NULL, 10);
                                //         break;
                                default:
                                        break;
                                }
                                i++;
                        }
                }
        }
}

static bool using_buf1 = true;

static void gps_uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
        static size_t current_bytes = 0;
        switch (evt->type)
        {

        case UART_RX_RDY:
                // printk("got something\n");
                // Check if a complete NMEA sentence has been received
                // printk("The new size is: ", evt->data.rx.len);
                if (evt->data.rx.len > GPS_RECEIVE_BUFF_SIZE)
                {

                        printk("Buffer overflow");
                        current_bytes = 0; // Reset buffer
                        break;
                }

                parse_nmea(evt->data.rx.buf + evt->data.rx.offset);
                break;

        case UART_RX_BUF_REQUEST:
                uart_rx_buf_rsp(dev, gps_rx_next_buf, sizeof(gps_rx_next_buf) - 1);
                break;
        case UART_RX_DISABLED:
                uart_rx_enable(dev, gps_rx_buf, sizeof gps_rx_buf, RECEIVE_TIMEOUT);
                break;

        default:
                break;
        }
}

int main(void)
{
        printk("\nStarting application!\r\n");
        if (!device_is_ready(gpsUart))
        {
                printk("GPS is not ready!\r\n");
                return 1;
        }
        else
        {
                printk("good");
        }
        int ret = uart_callback_set(gpsUart, gps_uart_cb, NULL);
        if (ret)
        {
                printk("gps UART not set up right \r\n");
                return 1;
        }
        else
        {
                printk("good");
        }

        ret = uart_rx_enable(gpsUart, gps_rx_buf, sizeof gps_rx_buf, RECEIVE_TIMEOUT);
        if (ret)
        {
                printk("Could not enable gps rx\r\n");
                return 1;
        }
        else
        {
                printk("good");
        }

        while (1)
        {
                k_msleep(SLEEP_TIME);
                printk("Working\n");
                printGGA(gps.gpgga);
        }

        return 0;
}
