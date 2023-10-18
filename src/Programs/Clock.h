#pragma once
#include <Arduino.h>
#include "../Observers/TimeObserver.h"

#include "../Subjects/TimerSignalEmitter.h"
#include "Display.h"
class Clock : public TimeObserver
{
public:
    Clock(Display *display_);
    ~Clock();
    void display_time();
    void set_total_seconds(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void on_notify_second();

private:
    Display *display;
    TimerSignalEmitter *timer;
    uint total_seconds;
};