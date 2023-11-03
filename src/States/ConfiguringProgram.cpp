#include "ConfiguringProgram.h"

ConfiguringProgram::ConfiguringProgram(StateController &state_controller_, ProgramInterface &selected_program_) : StateInterface(state_controller_), selected_program(selected_program_)
{
    this->display = Display::get_instance();
    this->program_controller = ProgramController::get_instance();
    display->clear_display();
    display->clear_colon();
}

// This constructor handles transition from Idle phase triggered from a number input, rather than a directional.
ConfiguringProgram::ConfiguringProgram(StateController &state_controller_, ProgramInterface &selected_program_, uint8_t number_pressed) : StateInterface(state_controller_), selected_program(selected_program_)
{
    this->program_controller = ProgramController::get_instance();
    this->display = Display::get_instance();

    rounds_in = 1;
    config_state = state::work;

    display->clear_display();
    display->clear_colon();
    work_mm_ss_in[0] = number_pressed;
}

void ConfiguringProgram::ir_in(uint16_t *ir_command)
{
    switch (config_state)
    {
    case state::rounds:
        switch (*ir_command)
        {
        case IR_UP:
            rounds_in_rr[selected_digit_index] = (rounds_in_rr[selected_digit_index] == 9) ? rounds_in_rr[selected_digit_index] = 0 : ++rounds_in_rr[selected_digit_index];
            break;
        case IR_DOWN:
            rounds_in_rr[selected_digit_index] = (rounds_in_rr[selected_digit_index] == 0) ? rounds_in_rr[selected_digit_index] = 9 : --rounds_in_rr[selected_digit_index];
            break;
        case IR_LEFT:
        case IR_RIGHT:
            selected_digit_index = (selected_digit_index == 1) ? --selected_digit_index : ++selected_digit_index;
            break;
        case IR_1:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 1;
            break;
        case IR_2:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 2;
            break;
        case IR_3:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 3;
            break;
        case IR_4:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 4;
            break;
        case IR_5:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 5;
            break;
        case IR_6:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 6;
            break;
        case IR_7:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 7;
            break;
        case IR_8:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 8;
            break;
        case IR_9:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 9;
            break;
        case IR_0:
            rounds_in_rr[1] = rounds_in_rr[0];
            rounds_in_rr[0] = 0;
            break;
        case IR_OK:
            state_history.push(config_state);
            config_state = state::work;
            rounds_in = rounds_in_rr[1] * 10;
            rounds_in += rounds_in_rr[0];

            display->clear_display();
            selected_digit_index = 0;
            break;
        case IR_STAR:
            work_mm_ss_in[0] = work_mm_ss_in[1];
            work_mm_ss_in[1] = 0;
            break;
        case IR_HASH:
            state_controller.set_state(new NavigatingMenu(state_controller, selected_program.get_program_index())); // or go back to IDLE? Dont clear display here, because display isnt set immediately by state so it shows blank until next press
            break;
        default:
            break;
        }
        break;
    case state::work:
        switch (*ir_command)
        {
        case IR_RIGHT:
            selected_digit_index = (selected_digit_index == 0) ? selected_digit_index = 3 : --selected_digit_index;
            break;
        case IR_LEFT:
            selected_digit_index = (selected_digit_index == 3) ? selected_digit_index = 0 : ++selected_digit_index;
            break;
        case IR_UP:
            work_mm_ss_in[selected_digit_index] = (work_mm_ss_in[selected_digit_index] == 9) ? work_mm_ss_in[selected_digit_index] = 0 : ++work_mm_ss_in[selected_digit_index];
            break;
        case IR_DOWN:
            work_mm_ss_in[selected_digit_index] = (work_mm_ss_in[selected_digit_index] == 0) ? work_mm_ss_in[selected_digit_index] = 9 : --work_mm_ss_in[selected_digit_index];
            break;
        case IR_1:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 1;
            break;
        case IR_2:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 2;
            break;
        case IR_3:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 3;
            break;
        case IR_4:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 4;
            break;
        case IR_5:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 5;
            break;
        case IR_6:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 6;
            break;
        case IR_7:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 7;
            break;
        case IR_8:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 8;
            break;
        case IR_9:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 9;
            break;
        case IR_0:
            work_mm_ss_in[3] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[0];
            work_mm_ss_in[0] = 0;
            break;
        case IR_STAR:
            work_mm_ss_in[0] = work_mm_ss_in[1];
            work_mm_ss_in[1] = work_mm_ss_in[2];
            work_mm_ss_in[2] = work_mm_ss_in[3];
            work_mm_ss_in[3] = 0;
            break;
        case IR_OK:
            state_history.push(config_state);
            config_state = state::rest;

            work_seconds_in = work_mm_ss_in[0];
            work_seconds_in += work_mm_ss_in[1] * 10;
            work_seconds_in += work_mm_ss_in[2] * 60;
            work_seconds_in += work_mm_ss_in[3] * 600;

            display->clear_display();
            selected_digit_index = 0;

            break;
        case IR_HASH:
            previous_state();
            break;
        }
        break;
    case state::rest:
        switch (*ir_command)
        {
        case IR_RIGHT:
            selected_digit_index = (selected_digit_index == 0) ? selected_digit_index = 3 : --selected_digit_index;
            break;
        case IR_LEFT:
            selected_digit_index = (selected_digit_index == 3) ? selected_digit_index = 0 : ++selected_digit_index;
            break;
        case IR_UP:
            rest_mm_ss_in[selected_digit_index] = (rest_mm_ss_in[selected_digit_index] == 9) ? rest_mm_ss_in[selected_digit_index] = 0 : ++rest_mm_ss_in[selected_digit_index];
            break;
        case IR_DOWN:
            rest_mm_ss_in[selected_digit_index] = (rest_mm_ss_in[selected_digit_index] == 0) ? rest_mm_ss_in[selected_digit_index] = 9 : --rest_mm_ss_in[selected_digit_index];
            break;
        case IR_1:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 1;
            break;
        case IR_2:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 2;
            break;
        case IR_3:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 3;
            break;
        case IR_4:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 4;
            break;
        case IR_5:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 5;
            break;
        case IR_6:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 6;
            break;
        case IR_7:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 7;
            break;
        case IR_8:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 8;
            break;
        case IR_9:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 9;
            break;
        case IR_0:
            rest_mm_ss_in[3] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[0];
            rest_mm_ss_in[0] = 0;
            break;
        case IR_STAR:
            rest_mm_ss_in[0] = rest_mm_ss_in[1];
            rest_mm_ss_in[1] = rest_mm_ss_in[2];
            rest_mm_ss_in[2] = rest_mm_ss_in[3];
            rest_mm_ss_in[3] = 0;
            break;
        case IR_OK:
            state_history.push(config_state);
            config_state = state::direction;
            rest_seconds_in = rest_mm_ss_in[0];
            rest_seconds_in += rest_mm_ss_in[1] * 10;
            rest_seconds_in += rest_mm_ss_in[2] * 60;
            rest_seconds_in += rest_mm_ss_in[3] * 600;
            display->clear_display();
            break;
        case IR_HASH:
            previous_state();
            break;
        }
        break;
    case state::direction:
        switch (*ir_command)
        {
        case IR_UP:
        case IR_RIGHT:
        case IR_DOWN:
        case IR_LEFT:
            count_up = !count_up;
            break;
        case IR_OK:
            state_history.push(config_state);
            config_state = state::finished_configuring;
            display->clear_display();
            break;
        case IR_HASH:
            previous_state();
            break;
        }
        break;
    case state::finished_configuring:
        switch (*ir_command)
        {
        case IR_OK:
            program_controller->configure_selected_program(rounds_in, work_seconds_in, rest_seconds_in, count_up);
            state_controller.set_state(new PrelimCountdown(state_controller));
            break;
        case IR_STAR:
            previous_state();
            break;
        }
        break;
    }
}
void ConfiguringProgram::previous_state()
{
    if (!state_history.empty())
    {
        display->clear_display();
        config_state = state_history.top();
        state_history.pop();
        selected_digit_index = 0;
    }
    else
    {
        state_controller.set_state(new NavigatingMenu(state_controller, selected_program.get_program_index())); // or go back to IDLE? Dont clear display here, because display isnt set immediately by state so it shows blank until next press
    }
}

void ConfiguringProgram::run_display()
{
    switch (config_state)
    {
    case state::rounds:
        if (!selected_program.need_rounds)
        {
            config_state = state::work;
            selected_digit_index = 0;
            break;
        }
        display->write_string("rnd", 3, CRGB::Green);

        display->update_display(0, rounds_in_rr[0], CRGB::Red, (selected_digit_index == 0));
        display->update_display(1, rounds_in_rr[1], CRGB::Red, (selected_digit_index == 1));

        display->push_to_display();
        break;
    case state::work:
        if (!selected_program.need_work)
        {
            config_state = state::rest;
            break;
        }
        display->update_display(3, work_mm_ss_in[3], CRGB::Red, (selected_digit_index == 3));
        display->update_display(2, work_mm_ss_in[2], CRGB::Red, (selected_digit_index == 2));
        display->update_display(1, work_mm_ss_in[1], CRGB::Red, (selected_digit_index == 1));
        display->update_display(0, work_mm_ss_in[0], CRGB::Red, (selected_digit_index == 0));
        display->push_to_display();
        break;
    case state::rest:
        if (!selected_program.need_rest)
        {
            config_state = state::direction;
            break;
        }
        display->update_display(3, rest_mm_ss_in[3], CRGB::Green, (selected_digit_index == 3));
        display->update_display(2, rest_mm_ss_in[2], CRGB::Green, (selected_digit_index == 2));
        display->update_display(1, rest_mm_ss_in[1], CRGB::Green, (selected_digit_index == 1));
        display->update_display(0, rest_mm_ss_in[0], CRGB::Green, (selected_digit_index == 0));
        display->push_to_display();
        break;
    case state::direction:
        if (!selected_program.need_direction)
        {
            config_state = state::finished_configuring;
            break;
        }
        display->write_string((count_up) ? "up" : "dn", 2, CRGB::Red);
        display->push_to_display();
        break;
    case state::finished_configuring:
        // Can't display total seconds consistently in hold screen because some programs have their time set in the program initiatlization
        // because they are hard coded, and some programs rely on the input from this state. I could either call configure program first, in which case
        // the display is shown as 0seconds because this state hasn't been used, or I reference this states value for work seconds, in which case the hard
        // coded programs display 0 seconds, because this state isn't used.
        if (selected_program.program_runner.total_work_time != 0)
        {
            display->update_display(3, selected_program.program_runner.total_work_time / 600, CRGB::Red);
            display->update_display(2, selected_program.program_runner.total_work_time / 60 % 10, CRGB::Red);
            display->update_display(1, selected_program.program_runner.total_work_time / 10 % 6, CRGB::Red);
            display->update_display(0, selected_program.program_runner.total_work_time % 10, CRGB::Red);
        }
        else
        {
            display->update_display(3, work_seconds_in / 600, CRGB::Red);
            display->update_display(2, work_seconds_in / 60 % 10, CRGB::Red);
            display->update_display(1, work_seconds_in / 10 % 6, CRGB::Red);
            display->update_display(0, work_seconds_in % 10, CRGB::Red);
        }
        display->push_to_display();
        break;
    }
}