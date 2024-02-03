#pragma once

#include "../Interfaces/ProgramInterface.h"

class Qnd : public ProgramInterface
{
public:
    Qnd(uint8_t program_index_) : ProgramInterface("qnd   ", program_index_)
    {
        need_work = false;
        need_rest = false;
        need_rounds = true;
        need_direction = true;

        set_preset_values();
    }

    void special_program_init() override;
    void second_in() override;
    void second_in_dn();
    void second_in_up();
    void set_preset_values() override;

    uint8_t phase_number = 1; // Keeps track of the 4 phases in each round.
};