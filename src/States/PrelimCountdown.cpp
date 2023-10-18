#include "PrelimCountdown.h"

PrelimCountdown::PrelimCountdown(StateController &state_controller_) : StateInterface(state_controller_)
{
    display = Display::get_instance();
    timer = TimerSignalEmitter::get_instance(0);
    timer->add_observer(this);
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
        state_controller.set_state(new NavigatingMenu(state_controller));
        break;
    case IR_OK:
        // Pause
        is_paused = !is_paused;
        break;
    }
}

void PrelimCountdown::on_notify_second()
{
    Serial.println(countdown_seconds);
    if (!is_paused)
    {
        this->countdown_seconds--;
        // go to one, so the 0 tick is the state transition.
        if (this->countdown_seconds <= 3)
        {
            // beep
        }
        if (this->countdown_seconds <= 1)
        {
            state_controller.set_state(new Running(state_controller));
        }
    }
}

void PrelimCountdown::run_display()
{
    display->write_string("strt", 4, CRGB::Green);
    display->update_display(1, this->countdown_seconds / 10, (this->countdown_seconds / 10 == 1) ? CRGB::Green : CRGB::Black);
    display->update_display(0, this->countdown_seconds % 10, CRGB::Green);
    display->push_to_display();
}
