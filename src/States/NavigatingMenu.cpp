#include "NavigatingMenu.h"

NavigatingMenu::NavigatingMenu(StateController &state_controller_) : StateInterface(state_controller_)
{
    this->display = Display::get_instance();
    this->program_index = 0;
    this->program_controller = ProgramController::get_instance();
}

void NavigatingMenu::ir_in(uint16_t *ir_command)
{
    switch (*ir_command)
    {
    case IR_UP:
        this->program_index++;
        display->write_string(program_controller->get_program_name(this->program_index % NUM_PROGRAMS), 6, CRGB::Red);
    case IR_DOWN:
        this->program_index++;
        display->write_string(program_controller->get_program_name(this->program_index % NUM_PROGRAMS), 6, CRGB::Red);
        break;

    case IR_BACK:
        state_controller.set_state(new Idle(state_controller));
        break;
    case IR_OK:
        program_controller->set_selected_program(program_index);
        //state_controller.set_state(new ConfiguringProgram(state_controller));
        break;
    }
}
