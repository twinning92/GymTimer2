#include <Arduino.h>
#include <IRremote.hpp>

#include "Display.h"
#include "Programs/ProgramController.h"
#include "Programs/Clock.h"
#include "States/StateController.h"

#include "Subjects/TimerSignalEmitter.h"
#include "Subjects/IR.h"

#define TIMER_0 0

Display *display = nullptr;
ProgramController *prog_controller = nullptr;

IR *ir = nullptr;
TimerSignalEmitter *timer = nullptr;

StateController *state_controller = nullptr;

void setup()
{
  Serial.begin(115200);
  display = Display::get_instance();
  prog_controller = ProgramController::get_instance();
  ir = new IR();
  timer = new TimerSignalEmitter(TIMER_0);
  state_controller = new StateController(*ir);
}

void loop()
{
}
