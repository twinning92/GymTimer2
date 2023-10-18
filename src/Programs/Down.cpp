#include "Down.h"

void Down::special_program_init()
{
    program_runner.seconds_value = program_runner.total_work_time;
}

void Down::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.seconds_value--;
        if (program_runner.seconds_value <= 0)
        {
            program_runner.finished_program = true;
        }
    }
}
