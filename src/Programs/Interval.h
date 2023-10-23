#pragma once

#include "../Interfaces/ProgramInterface.h"

class Interval : public ProgramInterface
{
public:
    Interval(uint8_t program_index_) : ProgramInterface("int   ", program_index_)
    {
        need_work = true;
        need_rest = true;
        need_rounds = true;
        need_direction = true;

        program_runner.show_rounds = need_rounds;
    }

    void special_program_init() override;
    void second_in() override;
};