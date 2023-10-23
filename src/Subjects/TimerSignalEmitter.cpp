#include "TimerSignalEmitter.h"

TimerSignalEmitter *TimerSignalEmitter::instance = nullptr;
uint8_t TimerSignalEmitter::timer_divider = 0;

TimerSignalEmitter::TimerSignalEmitter(int8_t timer_number)
{
    TickType_t x_ticks_to_wait = pdMS_TO_TICKS(150);
    hw_timer = timerBegin(timer_number, 80, true);
    timerAlarmWrite(hw_timer, 100000, true);
    timerAttachInterrupt(hw_timer, on_timer, true);
    
}

TimerSignalEmitter *TimerSignalEmitter::get_instance(int8_t timer_number)
{
    if (instance == nullptr)
    {
        instance = new TimerSignalEmitter(timer_number);
    }
    return instance;
}

TimerSignalEmitter *TimerSignalEmitter::get_instance()
{
    if (instance == nullptr)
    {
        instance = get_instance(0);
    }
    return instance;
}

void TimerSignalEmitter::start_timer()
{
    timerAlarmEnable(this->hw_timer);
}

void TimerSignalEmitter::stop_timer()
{
    timerAlarmDisable(this->hw_timer);
}

void IRAM_ATTR TimerSignalEmitter::on_timer()
{
    timer_divider++;
    buzzer.on_timer();

    // One second increments:
    if(timer_divider == 10)
    {
        instance->notify_observers();
        timer_divider = 0;
    }
}

void TimerSignalEmitter::notify_observers()
{
    notify_second();
}