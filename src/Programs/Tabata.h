#pragma once

#include "../Interfaces/ProgramInterface.h"

class Tabata : public ProgramInterface
{
public:
    Tabata() : ProgramInterface("tabata")
    {
        need_work = false;
        need_rest = false;
        need_rounds = false;

        program_runner.show_rounds = true;
    }

    void special_program_init() override;
    void second_in() override;
};