#include "Tabata.h"

void Tabata::special_program_init()
{
    program_runner.total_rounds = 8;
    program_runner.total_work_time = 20;
    program_runner.total_rest_time = 10;
    program_runner.seconds_value = program_runner.total_work_time;
}

void Tabata::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.seconds_value--;
        if (program_runner.rounds_value > 0)
        {
            if (program_runner.currently_working)
            {
                if (program_runner.seconds_value <= 0)
                {
                    program_runner.seconds_value = program_runner.total_rest_time;
                    program_runner.currently_working = false;
                    program_runner.rounds_value--;
                }
            }
            else
            {
                if (program_runner.seconds_value <= 0)
                {
                    program_runner.seconds_value = program_runner.total_work_time;
                    program_runner.currently_working = true;
                }
            }
        }
        else
        {
            program_runner.finished_program = true;
        }
    }
}