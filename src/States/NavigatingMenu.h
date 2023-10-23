#pragma once
#include "StateController.h"
#include "../Interfaces/IStateController.h"
#include "Display.h"
#include "../States/ConfiguringProgram.h"

class NavigatingMenu : public StateInterface
{
public:
    NavigatingMenu(StateController &state_controller_, uint8_t start_index);
    void ir_in(uint16_t *ir_command) override;
    void run_display() override;

private:
    int8_t program_index;
    Display *display;
    ProgramController *program_controller;
};