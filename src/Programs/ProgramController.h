#pragma once
#include <Arduino.h>
#include "../Interfaces/ProgramInterface.h"
#include "Observers/TimeObserver.h"
#include "Subjects/TimerSignalEmitter.h"

#include "Programs/Jits.h"
#include "Programs/Jits5.h"
#include "Programs/Jits7.h"
#include "Programs/DownRound.h"
#include "Programs/Tabata.h"
#include "Programs/Interval.h"
#include "Programs/Qnd.h"

#define NUM_PROGRAMS 7

class ProgramController : public TimeObserver
{
public:
    static ProgramController *get_instance();
    String get_program_name(int8_t query_program_index);
    void set_selected_program(int8_t selected_program_index);
    void configure_selected_program(int8_t rounds_in, int16_t work_in, int16_t rest_in, bool count_up);
    void on_notify_second() override;
    void start();
    void stop();

    ProgramInterface *selected_program;

private:
    ProgramController();
    static ProgramController *instance;
    static std::array<ProgramInterface *, NUM_PROGRAMS> program_array;

    TimerSignalEmitter *timer;
};