#include "UpRound.h"

void UpRound::special_program_init()
{
    program_runner.rounds_value = 1;
}

void UpRound::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.seconds_value++;
        if (program_runner.total_work_time - program_runner.seconds_value <= 0)
        {
            program_runner.rounds_value++;
            program_runner.seconds_value = 0;
            if (program_runner.total_rounds - (program_runner.rounds_value - 1) <= 0) // Offsetting the special_program_init of 1. This ensures we get a display starting at 1, and ending at total_rounds
            {
                program_runner.finished_program = true;
            }
        }
    }
}
