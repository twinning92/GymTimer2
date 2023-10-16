#pragma once
#include <Arduino.h>
#include "ProgramInterface.h"
#include "Observers/TimeObserver.h"
#include "Subjects/TimerSignalEmitter.h"

#define NUM_PROGRAMS 2

class ProgramController
{
public:
    static ProgramController *get_instance();
    String get_program_name(int8_t query_program_index);
    void set_selected_program(int8_t selected_program_index);

private:
    ProgramController();
    static ProgramController *instance;
    ProgramInterface *selected_program;
    static std::array<ProgramInterface *, NUM_PROGRAMS> program_array;
};