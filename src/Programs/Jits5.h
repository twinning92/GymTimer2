#pragma once
#include "../Interfaces/ProgramInterface.h"

// TODO: just make jits an interface?
class Jits5 : public ProgramInterface
{
public:
    Jits5(uint8_t program_index_) : ProgramInterface("5-jits", program_index_)
    {
        need_work = false;
        need_rest = false;
        need_rounds = false;
        need_direction = false;

        program_runner.show_rounds = true;
        reset_program();
    }

    void special_program_init() override;
    void second_in() override;
    void reset_program() override;
};