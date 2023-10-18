#pragma once
#include "StateController.h"
#include "Display.h"

#include "../Interfaces/StateInterface.h"
#include "../Subjects/TimerSignalEmitter.h"
#include "../Observers/TimeObserver.h"

#include "../States/Running.h"

class PrelimCountdown : public StateInterface, public TimeObserver
{
public:
    PrelimCountdown(StateController &state_controller_);
    ~PrelimCountdown();
    void ir_in(uint16_t *ir_command) override;
    void on_notify_second() override;

    void run_display() override;

private:
    bool is_paused = false;
    TimerSignalEmitter *timer;
    int8_t countdown_seconds = 10;
    Display *display;
};