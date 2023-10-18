#include "Running.h"

Running::Running(StateController &state_controller_) : StateInterface(state_controller_), program_controller(ProgramController::get_instance()), prog_runner(program_controller->selected_program->program_runner)
{
    timer = TimerSignalEmitter::get_instance(0);
    display = Display::get_instance();
    display->clear_display();
    program_controller->start();
}

void Running::ir_in(uint16_t *ir_command)
{
    switch (*ir_command)
    {
    case IR_0:
        prog_runner.finished_program = true;
        break;

    case IR_OK:
        prog_runner.paused = !prog_runner.paused;
        break;
    }
}

void Running::run_display()
{
    if (!prog_runner.finished_program)
    {
        if (prog_runner.show_rounds)
        {
            display->update_display(5, prog_runner.rounds_value / 10, (prog_runner.rounds_value / 10 != 0) ? prog_runner.round_colour : CRGB::Black);
            display->update_display(4, prog_runner.rounds_value % 10, prog_runner.round_colour);
        }

        display->update_display(3, prog_runner.seconds_value / 600, (prog_runner.currently_working) ? CRGB::Red : CRGB::Green, (prog_runner.paused) ? true : false);
        display->update_display(2, prog_runner.seconds_value / 60, (prog_runner.currently_working) ? CRGB::Red : CRGB::Green, (prog_runner.paused) ? true : false);
        display->update_display(1, prog_runner.seconds_value / 10 % 6, (prog_runner.currently_working) ? CRGB::Red : CRGB::Green, (prog_runner.paused) ? true : false);
        display->update_display(0, prog_runner.seconds_value % 10, (prog_runner.currently_working) ? CRGB::Red : CRGB::Green, (prog_runner.paused) ? true : false);
        Serial.println(prog_runner.seconds_value / 10);
        display->push_to_display();
    }
    else
    {
        // Absolutely filthy. But I can't utilise millis(), as this is being called in the loop for an indefinite amount of time. Other blinking function also blinks forever, the difference there being that the program will move on and update
        //  the display. The intention of this snippet is to just blink the numbers for a few seconds after the program completes.
        for (int i = 0; i < 370; i++)
        {
            display->update_display(3, 0, CRGB::Red, true);
            display->update_display(2, 0, CRGB::Red, true);
            display->update_display(1, 0, CRGB::Red, true);
            display->update_display(0, 0, CRGB::Red, true);
            display->push_to_display();
        }
        state_controller.set_state(new Idle(state_controller));
        program_controller->stop();
    }
}
