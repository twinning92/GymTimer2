#include "Jits5.h"

void Jits5::special_program_init()
{
    program_runner.total_work_time = 5 * 60;
    program_runner.total_rest_time = 1 * 60;
    program_runner.seconds_value = program_runner.total_work_time;
    program_runner.rounds_value = 1;
    program_runner.total_rounds = 99;
}

void Jits5::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.seconds_value--;
        if (program_runner.currently_working)
        {
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(1);
            }
            if (program_runner.seconds_value <= 0)
            {
                program_runner.seconds_value = program_runner.total_rest_time;
                program_runner.currently_working = false;
                buzzer.start(3);
            }
        }
        else
        {
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(1);
            }
            if (program_runner.seconds_value <= 0)
            {
                program_runner.rounds_value++;
                program_runner.seconds_value = program_runner.total_work_time;
                program_runner.currently_working = true;
                buzzer.start(3);
            }
        }
    }
}