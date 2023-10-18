#include "ProgramController.h"

ProgramController *ProgramController::instance = nullptr;
std::array<ProgramInterface *, NUM_PROGRAMS> ProgramController::program_array;

ProgramController::ProgramController()
{
    program_array[0] = new DownRound();
    this->selected_program = nullptr;
    timer = TimerSignalEmitter::get_instance();
    timer->add_observer(this);
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

void ProgramController::configure_selected_program(int8_t rounds_in, int16_t work_in, int16_t rest_in)
{
    this->selected_program->program_runner.total_rounds = rounds_in;
    this->selected_program->program_runner.total_work_time = work_in;
    this->selected_program->program_runner.total_rest_time = rest_in;
}

void ProgramController::on_notify_second()
{
    if (selected_program != nullptr)
    {
        selected_program->second_in();
    }
}
