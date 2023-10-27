#include "Tabata.h"

void Tabata::special_program_init()
{
    set_preset_values();
}

void Tabata::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.seconds_value--;
        if (program_runner.currently_working)
        {
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(10 * 1);
            }
            if (program_runner.seconds_value <= 0)
            {
                if (program_runner.rounds_value <= 1)
                {
                    program_runner.finished_program = true;
                    buzzer.start(10 * 10);
                }
                else
                {
                    program_runner.seconds_value = program_runner.total_rest_time;
                    program_runner.currently_working = false;
                    buzzer.start(10 * 3);
                }
            }
        }
        else // rest
        {
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(10 * 1);
            }
            if (program_runner.seconds_value <= 0)
            {
                program_runner.seconds_value = program_runner.total_work_time;
                program_runner.currently_working = true;
                program_runner.rounds_value--;
                buzzer.start(10 * 3);
            }
        }
    }
}

void Tabata::set_preset_values()
{
    need_work = false;
    need_rest = false;
    need_rounds = false;
    need_direction = false;
    program_runner.show_rounds = true;
    program_runner.total_rounds = 8;
    program_runner.total_work_time = 20;
    program_runner.total_rest_time = 10;
    program_runner.seconds_value = program_runner.total_work_time;
    program_runner.rounds_value = program_runner.total_rounds;
}
