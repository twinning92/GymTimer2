#include "Running.h"

Running::Running(StateController &state_controller_) : StateInterface(state_controller_)
{
    timer = TimerSignalEmitter::get_instance();
    display = Display::get_instance();
}

void Running::ir_in(uint16_t *ir_command)
{
}

void Running::run_display()
{
}
