#include "NavigatingMenu.h"

NavigatingMenu::NavigatingMenu(StateController &state_controller_, uint8_t start_index) : StateInterface(state_controller_)
{
    this->display = Display::get_instance();
    this->program_controller = ProgramController::get_instance();
    this->program_index = start_index;
    display->clear_colon();
}

void NavigatingMenu::ir_in(uint16_t *ir_command)
{
    switch (*ir_command)
    {
    case IR_RIGHT:
    case IR_UP:
        this->program_index = (this->program_index + 1) % NUM_PROGRAMS;
        break;
    case IR_LEFT:
    case IR_DOWN:
        this->program_index = (this->program_index - 1 + NUM_PROGRAMS) % NUM_PROGRAMS;
        break;
    case IR_1:
        this->program_index = 0;
        break;
    case IR_2:
        this->program_index = 1;
        break;
    case IR_3:
        this->program_index = 2;
        break;
    case IR_4:
        this->program_index = 3;
        break;
    case IR_5:
        this->program_index = 4;
        break;
    case IR_6:
        this->program_index = 5;
        break;
    case IR_HASH:
    case IR_STAR:
        state_controller.set_state(new Idle(state_controller));
        break;
    case IR_OK:
        program_controller->set_selected_program(program_index);
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program));
        break;
    default:
        break;
    }
}

void NavigatingMenu::run_display()
{
    display->write_string(program_controller->get_program_name(this->program_index % NUM_PROGRAMS), 6, CRGB::Red);
    display->push_to_display();
}
