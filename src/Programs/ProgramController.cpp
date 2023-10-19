#include "ProgramController.h"

ProgramController *ProgramController::instance = nullptr;
std::array<ProgramInterface *, NUM_PROGRAMS> ProgramController::program_array;

ProgramController::ProgramController()
{
    program_array[0] = new Jits();
    program_array[1] = new DownRound();
    program_array[2] = new Down();
    program_array[3] = new UpRound();
    program_array[4] = new Up();
    program_array[5] = new Jits5();
    program_array[6] = new Jits7();
    program_array[7] = new Interval();
    program_array[8] = new Tabata();
    this->selected_program = nullptr;
    timer = TimerSignalEmitter::get_instance();
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
    this->selected_program->program_runner.rounds_value = rounds_in;

    this->selected_program->program_runner.total_work_time = work_in;
    this->selected_program->program_runner.total_rest_time = rest_in;
    this->selected_program->special_program_init();
}

void ProgramController::on_notify_second()
{
    if (selected_program != nullptr)
    {
        selected_program->second_in();
    }
}

void ProgramController::start()
{
    timer->add_observer(this);
}

void ProgramController::stop()
{
    selected_program->reset_program();
    timer->remove_observer(this);
}
