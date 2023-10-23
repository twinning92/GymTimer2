#pragma once

#include "../Interfaces/ProgramInterface.h"

class DownRound : public ProgramInterface
{
public:
    DownRound(uint8_t program_index_) : ProgramInterface("rounds", program_index_)
    {
        need_rounds = true;
        need_rest = false;
        need_work = true;
        need_direction = true;

        program_runner.show_rounds = need_rounds;
    };
    void special_program_init() override;
    void second_in() override;
};