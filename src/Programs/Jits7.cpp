#include "Jits7.h"

void Jits7::special_program_init()
{
    set_preset_values();
}

void Jits7::second_in()
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
                program_runner.seconds_value = program_runner.total_rest_time;
                program_runner.currently_working = false;
                buzzer.start(10 * 3);
            }
        }
        else
        {
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(10 * 1);
            }
            if (program_runner.seconds_value <= 0)
            {
                program_runner.rounds_value++;
                program_runner.seconds_value = program_runner.total_work_time;
                program_runner.currently_working = true;
                buzzer.start(10 * 3);
            }
        }
    }
}

void Jits7::set_preset_values()
{
    program_runner.currently_working = true;
    program_runner.finished_program = false;
    program_runner.paused = false;

    program_runner.total_work_time = 7 * 60;
    program_runner.total_rest_time = 1.5 * 60;
    program_runner.seconds_value = program_runner.total_work_time;
    program_runner.rounds_value = 1;
    program_runner.total_rounds = 99;
}
