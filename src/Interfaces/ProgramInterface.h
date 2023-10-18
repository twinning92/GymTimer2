#pragma once
#include <Arduino.h>

#include "../Observers/IRObserver.h"
#include "../Observers/TimeObserver.h"
#include <FastLED.h>

// Need both IR and Time to configure and run programs.
class ProgramInterface
{
protected:
    String program_name;

    uint16_t seconds_to_work = 0;
    uint16_t seconds_to_rest = 0;
    uint8_t total_num_rounds = 0;

public:
    ProgramInterface(String program_name_);

    const String get_name();

    // virtual void start() = 0;
    virtual void second_in() = 0;
    virtual void special_program_init() = 0;
    void reset_program();
    virtual ~ProgramInterface() = default;
    bool need_rounds = false;
    bool need_work = false;
    bool need_rest = false;
    struct program_runner
    {
        bool paused = false;
        bool beep = false;
        bool show_rounds;
        bool currently_working = true;
        bool finished_program = false;

        CRGB round_colour = CRGB::Green;

        int8_t total_rounds = 0; // Store number of rounds. Don't devrement this one. In case we want to reuse this?
        int16_t total_work_time = 0;
        int16_t total_rest_time = 0;

        int8_t rounds_value = 0;   // Rounds value to actually display
        int16_t seconds_value = 0; // Use seconds value to increment and calculate off. This is what is sent to the display.
        int16_t beep_milliseconds = 0;
    } program_runner;
};
