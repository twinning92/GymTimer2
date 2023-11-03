#include "Clock.h"

Clock::Clock() 
{
    display = Display::get_instance();
}

Clock::~Clock()
{
}

void Clock::display_time(CRGB colour)
{
    gps_sensor.get_gps_time(&hours, &minutes, &seconds);
    if (hours != 69)
    {
        // Serial.println(hours);
        uint8_t low_seconds = seconds % 10;
        uint8_t high_seconds = seconds / 10 % 6;

        uint8_t low_minutes = minutes % 10;
        uint8_t high_minutes = minutes / 10;

        uint8_t low_hours = hours % 10;
        uint8_t high_hours = hours / 10;

        // display->update_display(0, low_seconds, (CRGB)colours[colour_index]);
        // display->update_display(1, high_seconds, (CRGB)colours[colour_index]);
        // display->update_display(2, low_minutes, (CRGB)colours[colour_index]);
        // display->update_display(3, high_minutes, (CRGB)colours[colour_index]);
        // display->update_display(4, low_hours, (CRGB)colours[colour_index]);
        // display->update_display(5, high_hours, (CRGB)colours[colour_index]);
        display->update_display(0, low_seconds, colour);
        display->update_display(1, high_seconds, colour);
        display->update_display(2, low_minutes, colour);
        display->update_display(3, high_minutes, colour);
        display->update_display(4, low_hours, colour);
        display->update_display(5, high_hours, colour);
        display->push_to_display();

        (low_seconds % 2 == 0) ? display->toggle_colon(colour) : display->clear_colon();
        // Serial.printf("%d%d:%d%d:%d%d\n", high_hours, low_hours, high_minutes, low_minutes, high_seconds, low_seconds);
    }
    else
    {
        display->write_string(" gps  ", 6, CRGB::Red, true);
        display->push_to_display();
    }
}