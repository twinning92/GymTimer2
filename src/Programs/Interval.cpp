#include "Interval.h"

void Interval::special_program_init()
{
    if (!program_runner.count_up)
    {
        program_runner.seconds_value = program_runner.total_work_time;
    }
}

void Interval::second_in()
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
