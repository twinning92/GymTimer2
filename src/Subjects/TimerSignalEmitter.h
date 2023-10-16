#pragma once
#include <Arduino.h>
#include "TimeSubject.h"

class TimerSignalEmitter : public TimeSubject
{
public:
    TimerSignalEmitter(int8_t timer_number);
    void start_timer();
    void stop_timer();

private:
    static void IRAM_ATTR on_timer();
    void notify_observers();

    hw_timer_t *hw_timer = nullptr;
    static TimerSignalEmitter *tse;
};