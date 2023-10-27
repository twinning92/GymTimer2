#include "PrelimCountdown.h"

PrelimCountdown::PrelimCountdown(StateController &state_controller_) : StateInterface(state_controller_)
{
    display = Display::get_instance();
    timer = TimerSignalEmitter::get_instance(0);
    program_controller = ProgramController::get_instance();
    timer->add_observer(this);
    display->clear_colon();
}

PrelimCountdown::~PrelimCountdown()
{
    timer->remove_observer(this);
}

void PrelimCountdown::ir_in(uint16_t *ir_command)
{
    switch (*ir_command)
    {
    case IR_BACK:
        state_controller.set_state(new ConfiguringProgram(state_controller, *program_controller->selected_program));
        break;
    case IR_OK:
        // Pause
        is_paused = !is_paused;
        break;
    case IR_HASH:
        state_controller.set_state(new Idle(state_controller));
        break;
    }
}

void PrelimCountdown::on_notify_second()
{
    if (!is_paused)
    {
        this->countdown_seconds--;
        // go to one, so the 0 tick is the state transition.
        if (this->countdown_seconds <= 3 && this->countdown_seconds > 0)
        {
            buzzer.start(10 * 1);
        }
        if (this->countdown_seconds <= 0)
        {
            buzzer.start(10 * 3);
            state_controller.set_state(new Running(state_controller));
        }
    }
}

void PrelimCountdown::run_display()
{
    display->write_string("strt", 4, CRGB::Green);
    display->update_display(1, this->countdown_seconds / 10, (this->countdown_seconds / 10 == 1) ? CRGB::Green : CRGB::Black, (is_paused) ? true : false);
    display->update_display(0, this->countdown_seconds % 10, CRGB::Green, (is_paused) ? true : false);
    display->push_to_display();
}
