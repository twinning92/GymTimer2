#include "ProgramController.h"

ProgramController *ProgramController::instance = nullptr;
std::array<ProgramInterface *, NUM_PROGRAMS> ProgramController::program_array;

ProgramController::ProgramController()
{
    program_array[0] = new DownRound();
}

ProgramController *ProgramController::get_instance()
{
    if (instance == nullptr)
    {
        instance = new ProgramController();
    }
    return instance;
}

String ProgramController::get_program_name(int8_t query_program_index)
{
    return program_array[query_program_index]->get_name();
}

void ProgramController::set_selected_program(int8_t selected_program_index)
{
    this->selected_program = program_array[selected_program_index];
}
