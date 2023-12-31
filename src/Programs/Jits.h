#pragma once

#include "../Interfaces/ProgramInterface.h"

class Jits : public ProgramInterface
{
public:
    Jits(uint8_t program_index_) : ProgramInterface("jits", program_index_)
    {
        need_work = true;
        need_rest = true;
        need_rounds = false;
        need_direction = false;

        program_runner.show_rounds = true;
    }

    void special_program_init() override;
    void second_in() override;
};