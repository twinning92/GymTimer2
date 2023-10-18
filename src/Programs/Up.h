#pragma once

#include "../Interfaces/ProgramInterface.h"

class Up : public ProgramInterface
{
public:
    Up() : ProgramInterface("up    ")
    {
        need_rounds = false;
        need_rest = false;
        need_work = true;

        program_runner.show_rounds = need_rounds;
    };
    void special_program_init() override;
    void second_in() override;
};