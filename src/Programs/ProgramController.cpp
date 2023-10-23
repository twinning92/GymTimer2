#include "ProgramController.h"

ProgramController *ProgramController::instance = nullptr;
std::array<ProgramInterface *, NUM_PROGRAMS> ProgramController::program_array;

ProgramController::ProgramController()
{
    program_array[0] = new Jits(0);
    program_array[1] = new DownRound(1);
    program_array[2] = new Interval(2);
    program_array[3] = new Jits5(3);
    program_array[4] = new Jits7(4);
    program_array[5] = new Tabata(5);
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

void ProgramController::configure_selected_program(int8_t rounds_in, int16_t work_in, int16_t rest_in, bool count_up)
{
    this->selected_program->program_runner.total_rounds = rounds_in;
    this->selected_program->program_runner.rounds_value = rounds_in;

    this->selected_program->program_runner.total_work_time = work_in;
    this->selected_program->program_runner.total_rest_time = rest_in;

    this->selected_program->program_runner.count_up = count_up;
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
