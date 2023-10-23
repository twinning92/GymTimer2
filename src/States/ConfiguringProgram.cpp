#include "ConfiguringProgram.h"

ConfiguringProgram::ConfiguringProgram(StateController &state_controller_, ProgramInterface &selected_program_) : StateInterface(state_controller_), selected_program(selected_program_)
{
    this->display = Display::get_instance();
    this->program_controller = ProgramController::get_instance();
    // Init the rounds display to start at 1 instead of 0.
    rounds_in_rr[0] = 1;
    display->clear_display();
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
        case IR_OK:
            state_history.push(config_state);
            config_state = state::work;
            rounds_in = rounds_in_rr[1] * 10;
            rounds_in += rounds_in_rr[0];

            display->clear_display();
            selected_digit_index = 3;
            break;
        case IR_BACK:
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
        case IR_OK:
            state_history.push(config_state);
            config_state = state::rest;

            work_seconds_in = work_mm_ss_in[0];
            work_seconds_in += work_mm_ss_in[1] * 10;
            work_seconds_in += work_mm_ss_in[2] * 60;
            work_seconds_in += work_mm_ss_in[3] * 600;

            display->clear_display();
            selected_digit_index = 3;

            break;
        case IR_BACK:
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
        case IR_OK:
            state_history.push(config_state);
            config_state = state::direction;
            rest_seconds_in = rest_mm_ss_in[0];
            rest_seconds_in += rest_mm_ss_in[1] * 10;
            rest_seconds_in += rest_mm_ss_in[2] * 60;
            rest_seconds_in += rest_mm_ss_in[3] * 600;
            display->clear_display();
            break;
        case IR_BACK:
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
        case IR_BACK:
            previous_state();
            break;
        }
        break;
    case state::finished_configuring:
        switch (*ir_command)
        {
        case IR_OK:
            state_controller.set_state(new PrelimCountdown(state_controller));
            break;
        case IR_BACK:
            previous_state();
            break;
        case IR_0:
            state_controller.set_state(new Idle(state_controller));
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
    // Double switch between ir_in and run_display is a consequence of having the ir signal piped in. Can't have all the logic in ir_in otherwise nothing will be displayed until ir_signal received.
    switch (config_state)
    {
    case state::rounds:
        if (!selected_program.need_rounds)
        {
            config_state = state::work;
            selected_digit_index = 3;
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
        program_controller->configure_selected_program(rounds_in, work_seconds_in, rest_seconds_in, count_up);

        display->update_display(3, selected_program.program_runner.total_work_time / 600, CRGB::Red);
        display->update_display(2, selected_program.program_runner.total_work_time / 60 % 10, CRGB::Red);
        display->update_display(1, selected_program.program_runner.total_work_time / 10 % 6, CRGB::Red);
        display->update_display(0, selected_program.program_runner.total_work_time % 10, CRGB::Red);

        display->push_to_display();
        break;
    }
}