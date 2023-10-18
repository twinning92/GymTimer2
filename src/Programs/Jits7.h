#pragma once
#include "../Interfaces/ProgramInterface.h"

// TODO: just make jits an interface?
class Jits7 : public ProgramInterface
{
public:
    Jits7() : ProgramInterface("7-jits")
    {
        need_work = false;
        need_rest = false;
        need_rounds = false;

        program_runner.show_rounds = true;
    }

    void special_program_init() override;
    void second_in() override;
};