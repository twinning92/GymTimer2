#pragma once
#include "StateController.h"
#include "../Interfaces/StateInterface.h"
#include "../Subjects/IR.h"
#include "Display.h"
#include "PrelimCountdown.h"

class ConfiguringProgram : public StateInterface
{
public:
    ConfiguringProgram(StateController &state_controller_, ProgramInterface &selected_program_);
    void ir_in(uint16_t *ir_command) override;
    void run_display() override;

private:
    enum class state
    {
        rounds,
        work,
        rest,
        finished_configuring,
    };

    state config_state = state::rounds;
    int8_t selected_digit_index = 1;
    std::array<uint8_t, 2> rounds_in_rr = {0};
    std::array<uint8_t, 4> work_mm_ss_in = {0};
    std::array<uint8_t, 4> rest_mm_ss_in = {0};
    int8_t rounds_in = 0;
    int16_t work_seconds_in = 0;
    int16_t rest_seconds_in = 0;

    Display *display;
    ProgramController *program_controller;
    ProgramInterface &selected_program;
};