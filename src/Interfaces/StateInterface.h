#pragma once
#include <Arduino.h>
#include "Programs/ProgramController.h"

class StateController;
class ProgramController;

class StateInterface
{
public:
    StateInterface(StateController &state_controller_) : state_controller(state_controller_){};

        virtual void ir_in(uint16_t *ir_command) = 0;
    virtual void run_display() = 0;

    virtual ~StateInterface() = default;

protected:
    StateController &state_controller;
};