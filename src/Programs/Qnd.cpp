#include "Qnd.h"

void Qnd::special_program_init()
{
    set_preset_values();
}

void Qnd::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        if (!program_runner.count_up)
        {
            program_runner.seconds_value--;
        }
    }
}

void Qnd::set_preset_values()
{
    this->phase_number = 0;
    need_work = false;
    need_rest = false;
    need_rounds = true;
    need_direction = true;
    program_runner.show_rounds = true;
    program_runner.total_work_time = 30;
    program_runner.total_rest_time = 60;
    program_runner.seconds_value = program_runner.total_work_time;
    program_runner.rounds_value = program_runner.total_rounds;
}
