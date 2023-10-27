#include "GPS.h"

GPS::GPS() : gps_serial(2)
{
    gps_serial.begin(9600, SERIAL_8N1, RX, TX);
}

void GPS::get_gps_time(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    while (gps_serial.available() > 0)
    {
        if (gps.encode(gps_serial.read()))
        {
            if (gps.time.isValid())
            {
                *hour = gps.time.hour() + 8 % 24;
                *minute = gps.time.minute();
                *second = gps.time.second();
            }
            else
            {
                *hour = 69;
            }
        }
    }
}
