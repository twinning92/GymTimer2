#pragma once
#include <Arduino.h>
#include <TinyGPSPlus.h>

#define RX 16
#define TX 17

class GPS
{
public:
    GPS();
    void get_gps_time(uint8_t *hour, uint8_t *minute, uint8_t *second);

private:
    HardwareSerial gps_serial;
    TinyGPSPlus gps;
};

extern GPS gps_sensor;