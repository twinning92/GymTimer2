#include "ProgramInterface.h"

ProgramInterface::ProgramInterface(String program_name_)
{
    Serial.printf("Setting program name to: %s\n", program_name_);
    this->program_name = program_name_;
}

void ProgramInterface::start()
{
    this->program_runner.program_phase = Phase::TEN_SECOND_TO_START;
    this->program_runner.seconds_value = this->program_runner.ten_second_countdown;
    this->program_runner.total_rounds = this->total_num_rounds;
    this->program_runner.rounds_value = this->total_num_rounds;

    this->program_runner.total_work_time = this->seconds_to_work;
    this->program_runner.total_rest_time = this->seconds_to_rest;
}

const String ProgramInterface::get_name() { return program_name; }
