#pragma once
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define TEMP_PIN 2
class TempSensor
{
public:
    TempSensor() : dht(TEMP_PIN, DHT11)
    {
        pinMode(TEMP_PIN, INPUT);
        dht.begin();

        dht.temperature().getSensor(&temp_sensor);
        dht.humidity().getSensor(&temp_sensor);
    }

    float get_temperature()
    {
        sensors_event_t event;
        dht.temperature().getEvent(&event);
        if (!isnan(event.temperature))
        {
            return event.temperature;
        }
    }

    float get_humidity()
    {
        sensors_event_t event;
        dht.humidity().getEvent(&event);
        if (!isnan(event.relative_humidity))
        {
            return event.relative_humidity;
        }
    }

private:
    sensor_t temp_sensor;
    DHT_Unified dht;
};

extern TempSensor temp_sensor;