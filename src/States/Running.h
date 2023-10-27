#pragma once

#include "../Interfaces/StateInterface.h"
#include "../Interfaces/ProgramInterface.h"
#include "../States/StateController.h"

#include "../Display.h"
class Running : public StateInterface
{
public:
    Running(StateController &state_controller_);
    void ir_in(uint16_t *ir_command) override;
    void run_display() override;

private:
    ProgramController *program_controller;
    int8_t end_confirm_count = 0;
    struct ProgramInterface::program_runner &prog_runner;
    Display *display;
};