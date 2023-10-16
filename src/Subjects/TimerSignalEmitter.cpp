#include "TimerSignalEmitter.h"

TimerSignalEmitter *TimerSignalEmitter::tse = nullptr;

TimerSignalEmitter::TimerSignalEmitter(int8_t timer_number)
{
    TickType_t x_ticks_to_wait = pdMS_TO_TICKS(150);
    Serial.println("Timer construct");
    // Store this in the static pointer to use within the ISR
    tse = this;
    hw_timer = timerBegin(timer_number, 80, true);
    timerAlarmWrite(hw_timer, 1000000, true);
    timerAttachInterrupt(hw_timer, on_timer, true);
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
    tse->notify_observers();
}

void TimerSignalEmitter::notify_observers()
{
    notify_ir();
}