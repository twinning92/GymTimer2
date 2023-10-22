#include <Arduino.h>
#include <IRremote.hpp>

#include "Display.h"
#include "Programs/ProgramController.h"
#include "Programs/Clock.h"
#include "States/StateController.h"

#include "Subjects/TimerSignalEmitter.h"
#include "Subjects/IR.h"

#include "Sensors/TempSensor.h"
#include "Sensors/Buzzer.h"
// #include "Sensors/GPS.h"
#define TIMER_0 0

Display *display = nullptr;
ProgramController *prog_controller = nullptr;

IR *ir = nullptr;
TimerSignalEmitter *timer = nullptr;

Buzzer buzzer;
// GPS gps_sensor;

StateController *state_controller = nullptr;

void setup()
{
  Serial.begin(115200);
  display = Display::get_instance();
  timer = TimerSignalEmitter::get_instance(TIMER_0);
  timer->start_timer();
  prog_controller = ProgramController::get_instance();
  ir = new IR();
  state_controller = new StateController(*ir);
}

void loop()
{
  state_controller->run();
}

// TODO:
// - Once rounds are configured, display work time until user presses go. So input config -> OK -> **display work time** -> OK -> start 10 second countdown