#include "Interval.h"

void Interval::special_program_init()
{
    if (!program_runner.count_up)
    {
        program_runner.seconds_value = program_runner.total_work_time;
    }
    else
    {
        program_runner.rounds_value = 1;
    }
}

void Interval::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        if (!program_runner.count_up)
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
                    if (program_runner.rounds_value <= 1)
                    {
                        program_runner.finished_program = true;
                        buzzer.start(30);
                    }
                    else
                    {
                        program_runner.seconds_value = program_runner.total_rest_time;
                        program_runner.currently_working = false;
                        buzzer.start(3);
                    }
                }
            }
            else // rest
            {
                if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
                {
                    buzzer.start(1);
                }
                if (program_runner.seconds_value <= 0)
                {
                    program_runner.seconds_value = program_runner.total_work_time;
                    program_runner.currently_working = true;
                    program_runner.rounds_value--;
                    buzzer.start(3);
                }
            }
        }
    }
    else
    {
        program_runner.seconds_value++;

        if (program_runner.currently_working)
        {
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(1);
            }
            if (program_runner.total_work_time - program_runner.seconds_value <= 0)
            {

                if (program_runner.rounds_value >= program_runner.total_rounds)
                {
                    program_runner.finished_program = true;
                    buzzer.start(30);
                }
                else
                {
                    program_runner.seconds_value = program_runner.total_rest_time;
                    program_runner.seconds_value = 0;
                    program_runner.currently_working = false;
                    buzzer.start(3);
                }
            }
        }
        else // rest
        {
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(1);
            }
            if (program_runner.total_rest_time - program_runner.seconds_value <= 0)
            {
                program_runner.seconds_value = program_runner.total_work_time;
                program_runner.seconds_value = 0;
                program_runner.rounds_value++;
                if (program_runner.rounds_value <= program_runner.total_rounds)
                {
                    program_runner.currently_working = true;
                    buzzer.start(3);
                }
            }
        }
    }
}
