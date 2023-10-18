#pragma once

#include "../Interfaces/ProgramInterface.h"

class UpRound : public ProgramInterface
{
public:
    UpRound() : ProgramInterface("up rnd")
    {
        need_rounds = true;
        need_rest = false;
        need_work = true;

        program_runner.show_rounds = need_rounds;
    };
    void special_program_init() override;
    void second_in() override;
};