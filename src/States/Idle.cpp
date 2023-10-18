#include "Idle.h"

Clock *Idle::clock69 = nullptr;

void Idle::ir_in(uint16_t *ir_command)
{

    switch (*ir_command)
    {
    case IR_UP:
    case IR_DOWN:
        state_controller.set_state(new NavigatingMenu(state_controller));
    default:
        break;
    }
}

void Idle::run_display()
{
    clock69->display_time();
}
