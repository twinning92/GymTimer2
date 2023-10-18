#include "DownRound.h"

void DownRound::special_program_init()
{
    program_runner.seconds_value = program_runner.total_work_time;
}

void DownRound::second_in()
{
    // Need round count, but no rest transition.
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.seconds_value--;
        if (program_runner.seconds_value <= 0)
        {
            program_runner.rounds_value--;
            program_runner.seconds_value = program_runner.total_work_time;
            if (program_runner.rounds_value <= 0)
            {
                program_runner.finished_program = true;
            }
        }
    }
}
