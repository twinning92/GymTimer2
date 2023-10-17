#include "NavigatingMenu.h"

NavigatingMenu::NavigatingMenu(StateController &state_controller_) : StateInterface(state_controller_)
{
    this->display = Display::get_instance();
    this->program_controller = ProgramController::get_instance();
    this->program_index = 0;

    // Here we have to capture the first menu item, simply because the ir input gets consumed by the Idle state, leaving the screen blank until the next key press.
    display->write_string(program_controller->get_program_name(this->program_index % NUM_PROGRAMS), 6, CRGB::Red);
    display->push_to_display();
}

void NavigatingMenu::ir_in(uint16_t *ir_command)
{
    display->clear_display();
    switch (*ir_command)
    {
    case IR_UP:
        this->program_index++;
        display->write_string(program_controller->get_program_name(this->program_index % NUM_PROGRAMS), 6, CRGB::Red);
        display->push_to_display();
        break;

    case IR_DOWN:
        this->program_index++;
        display->write_string(program_controller->get_program_name(this->program_index % NUM_PROGRAMS), 6, CRGB::Red);
        display->push_to_display();
        break;

    case IR_BACK:
        state_controller.set_state(new Idle(state_controller));
        break;
    case IR_OK:
        program_controller->set_selected_program(program_index);
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program));
        break;
    }
}

void NavigatingMenu::run()
{
}
