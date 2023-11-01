#include "Idle.h"

Clock *Idle::clock69 = nullptr;

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
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program, 7));
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
    default:
        break;
    }
}

void Idle::run_display()
{
    clock69->display_time();
}
