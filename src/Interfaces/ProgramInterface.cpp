#include "ProgramInterface.h"

ProgramInterface::ProgramInterface(String program_name_)
{
    this->program_name = program_name_;
}

const String ProgramInterface::get_name() { return program_name; }

void ProgramInterface::reset_program()
{
    program_runner.currently_working = true;
    program_runner.finished_program = false;
    program_runner.paused = false;
    program_runner.rounds_value = 0;
    program_runner.seconds_value = 0;
    program_runner.total_rest_time = 0;
    program_runner.total_work_time = 0;
    program_runner.total_rounds = 0;
}
