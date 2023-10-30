#pragma once
#include "StateController.h"
#include "../Interfaces/StateInterface.h"
#include "NavigatingMenu.h"
#include "../Observers/TimeObserver.h"
#include "../Programs/Clock.h"

// Idle state. This will be responsible for running the clock, while this state is active.
// Display is obtained here, and then passed directly to the clock class, so that the class can update the display. It could be obtained directly in clock.
// Seconds are intercepted by the state interface, passed to this state, then the clock seconds counter is incremented from this state.
// The idea here is keep the state completely in control of the unit. Alternative would be to have the Clock program directly called by the Timer Subject, however then Idle knows nothing, not a big deal, but I think all programs will be run by Program Controller
// updating the internal values, and they can display themselves? Keeps it consistent across all programs. Clock is a special program, so i don't really want to use the program interface for it.

class Idle : public StateInterface
{
public:
    Idle(StateController &state_controller_) : StateInterface(state_controller_)
    {
        this->display = Display::get_instance();
        if (this->clock69 == nullptr)
        {
            this->clock69 = new Clock();
        }
    };
    ~Idle();
    void ir_in(uint16_t *ir_command) override;
    void run_display() override;

private:
    Display *display;
    static Clock *clock69;
};