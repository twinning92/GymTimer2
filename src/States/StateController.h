#pragma once
#include "../Interfaces/IStateController.h"
#include "../Interfaces/StateInterface.h"
#include "Subjects/IR.h"

#include "Observers/IRObserver.h"
#include "Observers/TimeObserver.h"

#include "States/Idle.h"
#include "States/NavigatingMenu.h"

class StateController : public IStateController, public IRObserver
{
public:
    StateController(IR &ir_);

    void set_state(StateInterface *new_state) override;
    void run();

    void on_notify_ir(uint16_t *ir_command) override;

protected:
    IR &ir;
    StateInterface *current_state;
};