#pragma once

#include "../Interfaces/ProgramInterface.h"

class Interval : public ProgramInterface
{
public:
    Interval() : ProgramInterface("int   ")
    {
        need_work = true;
        need_rest = true;
        need_rounds = true;

        program_runner.show_rounds = need_rounds;
    }

    void special_program_init() override;
    void second_in() override;
};