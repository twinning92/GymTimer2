#include "Clock.h"

Clock::Clock(Display *display_) : display(display_)
{
    timer = TimerSignalEmitter::get_instance();
    timer->add_observer(this);
}

void Clock::set_total_seconds(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    this->total_seconds = hours * 3600 + minutes * 60 + seconds;
}

void Clock::on_notify_second()
{
    this->total_seconds++;
}

void Clock::display_time()
{
    uint8_t low_seconds = total_seconds % 10;
    uint8_t high_seconds = total_seconds / 10 % 6;

    uint8_t total_minutes = (total_seconds / 60) % 60;
    uint8_t low_minutes = total_minutes % 10;
    uint8_t high_minutes = total_minutes / 10;

    uint8_t total_hours = (total_seconds / 3600) % 24;
    uint8_t low_hours = total_hours % 10;
    uint8_t high_hours = total_hours / 10;

    display->update_display(0, low_seconds);
    display->update_display(1, high_seconds);
    display->update_display(2, low_minutes);
    display->update_display(3, high_minutes);
    display->update_display(4, low_hours);
    display->update_display(5, high_hours);
    display->push_to_display();
}