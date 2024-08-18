#include "gps.h"
#include "main.h"
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>

#include <zephyr/drivers/uart.h>
#include <zephyr/devicetree.h>

#include <unistd.h>
#include <zephyr/device.h>
#include <stdlib.h>
#include <string.h>

static uint8_t gps_rx_next_buf[GPS_RECEIVE_BUFF_SIZE] = {0};
static uint8_t gps_rx_buf[GPS_RECEIVE_BUFF_SIZE] = {0};

void parse_nmea(const char *nmea_sentence, gpgps *gps)
{
    char *saveptr;
    char *line = strtok_r(nmea_sentence, "\n", &saveptr);
    char *id;
    while ((line = strtok_r(NULL, "\n", &saveptr)))
    {
        char *saveIDPointer;
        id = strtok_r(line, ",", &saveIDPointer);
        if (strcmp(id, "$GPGGA") == 0)
        {
            int i = 0;
            while ((id = strtok_r(NULL, ",", &saveIDPointer)))
            {
                switch (i)
                {
                case 0:
                    if (strlen(id) == 10)
                    {
                        strncpy(gps->gpgga.utcTime, id, 10);
                        gps->gpgga.utcTime[10] = '\0';
                    }

                    break;
                case 1:
                    if (strlen(id) == 9)
                    {
                        strncpy(gps->gpgga.latitude, id, 9);
                        gps->gpgga.latitude[9] = '\0';
                    }
                    break;
                case 2:
                    if (strlen(id) == 1)
                    {
                        gps->gpgga.nsIndicator = id[0];
                    }

                    break;
                case 3:
                    if (strlen(id) == 10)
                    {
                        strncpy(gps->gpgga.longitude, id, 10);
                        gps->gpgga.longitude[10] = '\0';
                    }
                    break;
                case 4:
                    if (strlen(id) == 1)
                    {
                        gps->gpgga.ewIndicator = id[0];
                    }
                    break;
                case 5:
                    if (strlen(id) == 1)
                    {
                        gps->gpgga.positionIndicator = id[0];
                    }
                    break;
                case 6:
                    if (strlen(id) == 2)
                    {
                        strncpy(gps->gpgga.numOfSatellites, id, 2);
                        gps->gpgga.numOfSatellites[2] = '\0';
                    }
                    break;
                case 7:
                    if (strlen(id) == 4)
                    {
                        strncpy(gps->gpgga.hdop, id, 4);
                        gps->gpgga.hdop[4] = '\0';
                    }
                    break;
                case 8:
                    if (strlen(id) == 4)
                    {
                        strncpy(gps->gpgga.mslAltitude, id, 4);
                        gps->gpgga.mslAltitude[4] = '\0';
                    }
                    break;
                case 9:
                    if (strlen(id) == 1)
                    {
                        gps->gpgga.altitudeUnits = id[0];
                    }
                    break;
                case 10:
                    if (strlen(id) == 5)
                    {
                        strncpy(gps->gpgga.geoidalSeparation, id, 5);
                        gps->gpgga.geoidalSeparation[5] = '\0';
                    }
                    break;
                case 11:
                    if (strlen(id) == 1)
                    {
                        gps->gpgga.geoidalUnits = id[0];
                    }
                    break;

                default:
                    break;
                }
                i++;
            }
        }
    }
}

static void gps_uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
    static size_t current_bytes = 0;
    switch (evt->type)
    {

    case UART_RX_RDY:
        if (evt->data.rx.len > GPS_RECEIVE_BUFF_SIZE)
        {

            printk("Buffer overflow");
            current_bytes = 0; // Reset buffer
            break;
        }

        parse_nmea(evt->data.rx.buf + evt->data.rx.offset, user_data);
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

int init_gps(const struct device *gpsUart, gpgps *gps)
{
    if (!device_is_ready(gpsUart))
    {
        printk("GPS is not ready!\r\n");
        return -1;
    }

    int ret = uart_callback_set(gpsUart, gps_uart_cb, gps);
    if (ret)
    {
        printk("gps UART not set up right \r\n");
        return -1;
    }

    ret = uart_rx_enable(gpsUart, gps_rx_buf, sizeof gps_rx_buf, RECEIVE_TIMEOUT);
    if (ret)
    {
        printk("Could not enable gps rx\r\n");
        return -1;
    }
    return 1;
}
