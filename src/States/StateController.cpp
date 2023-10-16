#include "StateController.h"

StateController::StateController(IR &ir_) : ir(ir_), current_state(nullptr)

{
    ir.add_observer(this);
    this->set_state(new Idle(*this));
    Serial.println("State set");
}

void StateController::set_state(StateInterface *new_state)
{
    if (current_state != nullptr)
    {
        delete current_state;
    }
    current_state = new_state;
}

void StateController::on_notify_ir()
{
    current_state->ir_in(ir.get_command());
}
