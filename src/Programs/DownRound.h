#pragma once

#include "../Interfaces/ProgramInterface.h"

class DownRound : public ProgramInterface
{
public:
    DownRound() : ProgramInterface("dn rnd")
    {
        need_rounds = true;
        need_rest = false;
        need_work = true;
    };
    void second_in() override;
};