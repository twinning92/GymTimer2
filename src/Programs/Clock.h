#pragma once
#include <Arduino.h>
#include "Display.h"
class Clock
{
public:
    Clock(Display *display_);

    void display_time();
    void set_total_seconds(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void tick();

private:
    Display *display;
    uint total_seconds;
};