#pragma once
#include <Arduino.h>
#include "../Interfaces/ProgramInterface.h"
#include "Observers/TimeObserver.h"
#include "Subjects/TimerSignalEmitter.h"

#include "Programs/DownRound.h"

#define NUM_PROGRAMS 1

class ProgramController
{
public:
    static ProgramController *get_instance();
    String get_program_name(int8_t query_program_index);
    void set_selected_program(int8_t selected_program_index);
    void configure_program();

    ProgramInterface *selected_program;

private:
    ProgramController();
    static ProgramController *instance;
    static std::array<ProgramInterface *, NUM_PROGRAMS> program_array;
};