#include "DownRound.h"

void DownRound::special_program_init()
{
    if (program_runner.count_up)
    {
        program_runner.rounds_value = 1;
    }
    else
    {
        program_runner.seconds_value = program_runner.total_work_time;
    }

    if (program_runner.total_rounds == 1)
    {
        program_runner.show_rounds = false;
    }
}

void DownRound::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        if (!program_runner.count_up)
        {
            program_runner.seconds_value--;
            if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
            {
                buzzer.start(1);
            }
            if (program_runner.seconds_value <= 0)
            {
                program_runner.rounds_value--;
                buzzer.start(3);
                program_runner.seconds_value = program_runner.total_work_time;
                if (program_runner.rounds_value <= 0)
                {
                    program_runner.finished_program = true;
                    buzzer.start(30);
                }
            }
        }

        else
        {
            program_runner.seconds_value++;
            if (program_runner.total_work_time - program_runner.seconds_value <= 3 && program_runner.total_work_time - program_runner.seconds_value > 0)
            {
                buzzer.start(1);
            }
            if (program_runner.total_work_time - program_runner.seconds_value <= 0)
            {
                program_runner.rounds_value++;
                buzzer.start(3);
                program_runner.seconds_value = 0;
                if (program_runner.total_rounds - (program_runner.rounds_value - 1) <= 0) // Offsetting the special_program_init of 1. This ensures we get a display starting at 1, and ending at total_rounds
                {
                    program_runner.finished_program = true;
                    buzzer.start(30);
                }
            }
        }
    }
}