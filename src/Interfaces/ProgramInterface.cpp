#include "ProgramInterface.h"

ProgramInterface::ProgramInterface(String program_name_)
{
    Serial.printf("Setting program name to: %s\n", program_name_);
    this->program_name = program_name_;
}

const String ProgramInterface::get_name() { return program_name; }
