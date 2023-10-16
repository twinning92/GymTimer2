#include "Idle.h"

void Idle::ir_in(uint16_t *ir_command)
{
    switch (*ir_command)
    {
    case IR_UP:
    case IR_DOWN:
        display->clear_display();
        state_controller.set_state(new NavigatingMenu(state_controller));
    default:
        break;
    }
}

void Idle::on_notify_second()
{
    // The state will catch the timer, then increment the clock number.
    Serial.println("tick");
    clock69->tick();
    clock69->display_time();
}
