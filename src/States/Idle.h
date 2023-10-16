#pragma once
#include "StateController.h"
#include "StateInterface.h"
#include "NavigatingMenu.h"
#include "../Observers/TimeObserver.h"
#include "../Programs/Clock.h"

// Idle state. This will be responsible for running the clock, while this state is active.
// Display is obtained here, and then passed directly to the clock class, so that the class can update the display. It could be obtained directly in clock.
// Seconds are intercepted here, and the clock seconds counter is incremented from this state.
// The idea here is keep the state completely in control of the unit. Alternative would be to have the Clock program directly called by the Timer Subject, however then Idle knows nothing, not a big deal, but I think all programs will be run by Program Controller
// updating the internal values, and they can display themselves? Keeps it consistent across all programs. Clock is a special program, so i don't really want to use the program interface for it.

class Idle : public StateInterface, public TimeObserver
{
public:
    Idle(StateController &state_controller_) : StateInterface(state_controller_)
    {
        this->display = Display::get_instance();
        this->clock69 = new Clock(display);

        // Change to query RTC time as new structure won't implement clock keeping time in the background. Could be achieved by moving clock into main class?
        clock69->set_total_seconds(10, 50, 10);
    };
    void ir_in(uint16_t *ir_command) override;
    void on_notify_second() override;

private:
    TimerSignalEmitter timer;
    Display *display;
    Clock *clock69;
};