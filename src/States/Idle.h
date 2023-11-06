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
        this->program_controller = ProgramController::get_instance();
        // Idle will set the selected program to DownRound. This way I can just pass selected program into Configure Program if the user enters a number during Idle Phase.
        this->program_controller->set_selected_program(1);
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
    ProgramController *program_controller;
    static Clock *clock69;

    bool display_buzz_words = false;
    std::array<String, 35> buzz_words = {"cunt", "fuck", "shit", "sick", "dardy", "cunty", "pussy", "good", "great", "congrats ", "personal best ", "again", "pity party ",
                                        "try harder ", "dog cunt ", "good shit ", "you can do it ", "I believe in you ", "great ass ", "fuckin hot shit dog cunt ", 
                                        "lets get that heart racing ", "find your fire ", "youre not tired ", "this isnt a tea party ", 
                                        "quit your crying this isnt daycare ", "feel the burn ", "you cant fake fit lift or quit ", 
                                        "do better ", "Ive seen toddlers push harder ", "cry on the inside like everyone else ", 
                                        "eat a bag of dicks ", "you go girl ", "boss babes dont quit ", "slay queen ", "slay the day "};
    uint8_t buzz_word_index = 0;

    std::array<String,2> iron = {"iron 0ctopus ", "iron 0ctopus school of physical culture "};
    uint8_t gym_name_index = 0;
    String easter_egg = "taylor is a sick cunt ";

    std::array<CRGB, 3> colours = {CRGB::Red, CRGB::Blue, CRGB::Green};
    static uint8_t colours_index;
    CRGB colour = colours[colours_index];

    enum class idle_state
    {
        clock,
        buzz_words,
        gym_name
    };
    idle_state state = idle_state::clock;
};