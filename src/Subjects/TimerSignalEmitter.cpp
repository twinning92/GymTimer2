#include "TimerSignalEmitter.h"

TimerSignalEmitter *TimerSignalEmitter::instance = nullptr;

TimerSignalEmitter::TimerSignalEmitter(int8_t timer_number)
{
    TickType_t x_ticks_to_wait = pdMS_TO_TICKS(150);
    Serial.println("Timer construct");
    hw_timer = timerBegin(timer_number, 80, true);
    timerAlarmWrite(hw_timer, 1000000, true);
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
    instance->notify_observers();
}

void TimerSignalEmitter::notify_observers()
{
    notify_second();
}