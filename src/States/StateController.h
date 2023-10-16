#pragma once
#include "IStateController.h"
#include "StateInterface.h"
#include "Subjects/IR.h"
#include "Observers/IRObserver.h"

#include "States/Idle.h"
#include "States/NavigatingMenu.h"

class StateController : public IStateController, public IRObserver
{
public:
    StateController(IR &ir_);
    void on_notify_ir() override;
    void set_state(StateInterface *new_state) override;
    e_state get_state() { return current_state->get_state(); };

protected:
    IR &ir;
    StateInterface *current_state;
};