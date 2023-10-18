#include "Up.h"

void Up::special_program_init()
{
}

void Up::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.seconds_value++;
        if (program_runner.total_work_time - program_runner.seconds_value <= 0)
        {
            program_runner.finished_program = true;
        }
    }
}
