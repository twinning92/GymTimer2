#pragma once
#include <Arduino.h>

#include "../Observers/IRObserver.h"
#include "../Observers/TimeObserver.h"

#include "../Sensors/Buzzer.h"
#include <FastLED.h>

// Need both IR and Time to configure and run programs.
class ProgramInterface
{
protected:
    String program_name;
    uint8_t program_index;

public:
    ProgramInterface(String program_name_, uint8_t program_index_);

    const String get_name();
    const uint8_t get_program_index();

    // virtual void start() = 0;

    virtual void second_in() = 0;
    virtual void special_program_init() = 0;
    virtual void set_preset_values();
    virtual ~ProgramInterface() = default;
    bool need_rounds = false;
    bool need_work = false;
    bool need_rest = false;
    bool need_direction = true;

    struct program_runner
    {
        bool paused = false;
        bool show_rounds;
        bool currently_working = true;
        bool finished_program = false;
        bool count_up = false;

        int8_t total_rounds = 0; // Store number of rounds. Don't devrement this one. In case we want to reuse this?
        int16_t total_work_time = 0;
        int16_t total_rest_time = 0;

        int8_t rounds_value = 0;   // Rounds value to actually display
        int16_t seconds_value = 0; // Use seconds value to increment and calculate off. This is what is sent to the display.
    } program_runner;
};
