#pragma once
#include "../Interfaces/ProgramInterface.h"

// TODO: just make jits an interface?
class Jits5 : public ProgramInterface
{
public:
    Jits5(uint8_t program_index_) : ProgramInterface("5-jits", program_index_)
    {
        need_work = false;
        need_rest = false;
        need_rounds = false;
        need_direction = false;

        program_runner.show_rounds = true;

        // We do this here so that configuring program state can correctly display the work time since it
        // doesn't have any idea about how long the work time is for this preconfigured programs as it uses the work sseconds entered within the state to display on the hold screen
        // Since these programs don't take configuring, if I set the preset values when program is instantiated then the correct work time can be displayed. When Configuring program state
        // is exited (forward to prelim countdown) it overwrites the work time etc to be 0.
        set_preset_values();
    }

    void special_program_init() override;
    void second_in() override;
    void set_preset_values() override;
};