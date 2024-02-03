#include "Qnd.h"

void Qnd::special_program_init()
{
    set_preset_values();
    program_runner.seconds_value = program_runner.count_up ? 0 : program_runner.total_work_time;
    program_runner.rounds_value = program_runner.count_up ? 1 : program_runner.total_rounds;
}

void Qnd::second_in_dn()
{
    program_runner.seconds_value--;
    if (program_runner.seconds_value <= 3 && program_runner.seconds_value > 0)
    {
        buzzer.start(10 * 1);
    }
    if (program_runner.seconds_value <= 0 && phase_number < 4)
    {
        phase_number++;
        if (phase_number == 4)
        {
            program_runner.seconds_value = program_runner.total_work_time + program_runner.total_rest_time;
        }
        else
        {
            program_runner.seconds_value = program_runner.total_work_time;
        }
        buzzer.start(10 * 3);
    }

    if (phase_number == 4)
    {
        if (program_runner.seconds_value <= program_runner.total_rest_time && program_runner.currently_working)
        {
            program_runner.currently_working = false;
            buzzer.start(10 * 1);
        }
        if (program_runner.seconds_value <= 0)
        {
            program_runner.rounds_value--;
            program_runner.seconds_value = program_runner.total_work_time;
            program_runner.currently_working = true;
            phase_number = 1;
            buzzer.start(10 * 3);
        }
        if (program_runner.rounds_value == 0)
        {
            program_runner.finished_program = true;
            // resetting the rounds when finished, as I don't actually have a specific 'reset' functions, only a 'preset' function, this means that I can't get different behaviour
            program_runner.total_rounds = 0;
            program_runner.rounds_value = 0;
            buzzer.start(10 * 10);
        }
    }
}

void Qnd::second_in_up()
{
    program_runner.seconds_value++;
    if (phase_number < 4 && program_runner.total_work_time - program_runner.seconds_value <= 3 && program_runner.total_work_time - program_runner.seconds_value > 0)
    {
        buzzer.start(10 * 1);
    }
    if (program_runner.seconds_value >= program_runner.total_work_time && phase_number < 4)
    {
        phase_number++;
        program_runner.seconds_value = 0;
        buzzer.start(10 * 3);
    }

    if (phase_number == 4)
    {
        if ((program_runner.total_work_time + program_runner.total_rest_time) - program_runner.seconds_value <= 3 && (program_runner.total_work_time + program_runner.total_rest_time) - program_runner.seconds_value > 0)
        {
            buzzer.start(10 * 1);
        }
        if (program_runner.seconds_value >= program_runner.total_work_time && program_runner.currently_working)
        {
            program_runner.currently_working = false;
            buzzer.start(10 * 1);
        }
        if (program_runner.seconds_value >= program_runner.total_rest_time + program_runner.total_work_time)
        {
            program_runner.rounds_value++;
            program_runner.seconds_value = 0;
            program_runner.currently_working = true;
            phase_number = 1;
            buzzer.start(10 * 3);
        }
        if (program_runner.rounds_value == program_runner.total_rounds + 1)
        {
            program_runner.finished_program = true;

            // resetting the rounds when finished, as I don't actually have a specific 'reset' functions, only a 'preset' function, this means that I can't get different behaviour
            program_runner.total_rounds = 0;
            program_runner.rounds_value = 0;
            buzzer.start(10 * 10);
        }
    }
}

void Qnd::second_in()
{
    if (!program_runner.paused && !program_runner.finished_program)
    {
        program_runner.count_up ? second_in_up() : second_in_dn();
    }
}

void Qnd::set_preset_values()
{
    if (program_runner.finished_program)
    {
        program_runner.rounds_value = 0;
        program_runner.total_rounds = 0;
    }
    program_runner.currently_working = true;
    program_runner.finished_program = false;
    program_runner.paused = false;
    this->phase_number = 1;
    program_runner.total_work_time = 10;
    program_runner.total_rest_time = 20;
}
