#pragma once

#include "../Interfaces/ProgramInterface.h"

class Qnd : public ProgramInterface
{
public:
    Qnd(uint8_t program_index_) : ProgramInterface("qnd   ", program_index_)
    {
        set_preset_values();
    }

    void special_program_init() override;
    void second_in() override;
    void set_preset_values() override;

    uint8_t phase_number = 0; // Keeps track of the 4 phases in each round.
};