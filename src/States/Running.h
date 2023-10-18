#pragma once

#include "../Interfaces/StateInterface.h"

#include "../States/StateController.h"

#include "../Display.h"
class Running : public StateInterface
{
public:
    Running(StateController &state_controller_);
    void ir_in(uint16_t *ir_command) override;
    void run_display() override;

private:
    TimerSignalEmitter *timer;
    Display *display;
};