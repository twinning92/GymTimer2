#include "Idle.h"

Clock *Idle::clock69 = nullptr;
uint8_t Idle::colours_index = 0;

Idle::~Idle()
{
    if (clock69 != nullptr)
    {
        delete clock69;
        clock69 = nullptr;
    }
}

void Idle::ir_in(uint16_t *ir_command)
{

    switch (*ir_command)
    {
    case IR_RIGHT:
    case IR_UP:
        state_controller.set_state(new NavigatingMenu(state_controller, 1));
        break;
    case IR_LEFT:
    case IR_DOWN:
        state_controller.set_state(new NavigatingMenu(state_controller, 0));
        break;
    case IR_1:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 1));
        break;
    case IR_2:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 2));
        break;
    case IR_3:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 3));
        break;
    case IR_4:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 4));
        break;
    case IR_5:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 5));
        break;
    case IR_6:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 6));
        break;
    case IR_7:
        if (state == idle_state::gym_name)
        {
            display->reset_scroll();
            display->scroll_string(easter_egg, easter_egg.length(), colour);
            display->push_to_display();
        }
        else
        {
            state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 7));
        }
        break;
    case IR_8:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 8));
        break;
    case IR_9:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 9));
        break;
    case IR_0:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 0));
        break;
    case IR_HASH:
        switch (state)
        {
        case idle_state::clock:
            display->clear_display();
            display->clear_colon();
            state = idle_state::buzz_words;
            break;
        case idle_state::buzz_words:
            display->reset_scroll();
            display->clear_display();
            display->clear_colon();
            state = idle_state::gym_name;
            break;
        case idle_state::gym_name:
            display->reset_scroll();
            display->clear_display();
            state = idle_state::clock;
        }
        break;
    case IR_OK:
        colours_index = (colours_index + 1) % colours.size();
        colour = colours[colours_index];
        break;
    case IR_STAR:
        if (state == idle_state::buzz_words)
        {
            display->clear_display();
            display->reset_scroll();

            buzz_word_index = (buzz_word_index + 1) % buzz_words.size();
        }
        else if (state == idle_state::gym_name)
        {
            display->clear_display();
            display->reset_scroll();
            gym_name_index = (gym_name_index + 1) % iron.size();
        }
        break;
    default:
        break;
    }
}

void Idle::run_display()
{
    switch (state)
    {
    case idle_state::buzz_words:
        if (buzz_words[buzz_word_index].length() <= 6)
        {
            display->write_string(buzz_words[buzz_word_index], buzz_words[buzz_word_index].length(), colour);
        }
        else
        {
            display->scroll_string(buzz_words[buzz_word_index], buzz_words[buzz_word_index].length(), colour);
        }
        display->push_to_display();

        break;
    case idle_state::gym_name:
        display->scroll_string(iron[gym_name_index], iron[gym_name_index].length(), colour);
        display->push_to_display();
        break;
    case idle_state::clock:
        clock69->display_time(colour);
        break;
    default:
        clock69->display_time(colour);
        break;
    }
}
