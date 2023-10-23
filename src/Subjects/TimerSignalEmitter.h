#pragma once
#include <Arduino.h>
#include "TimeSubject.h"
#include "../Sensors/Buzzer.h"

class TimerSignalEmitter : public TimeSubject
{
public:
    static TimerSignalEmitter *get_instance(int8_t timer_number);
    static TimerSignalEmitter *get_instance();
    void start_timer();
    void stop_timer();

private:
    TimerSignalEmitter(int8_t timer_number);
    static TimerSignalEmitter *instance;
    static uint8_t timer_divider;
    static void IRAM_ATTR on_timer();
    void notify_observers();

    hw_timer_t *hw_timer = nullptr;
};