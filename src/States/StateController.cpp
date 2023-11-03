#include "StateController.h"

StateController::StateController(IR &ir_) : ir(ir_), current_state(nullptr)
{
    ir.add_observer(this);
    this->set_state(new Idle(*this));
}

StateController::~StateController()
{
    ir.remove_observer(this);
}

void StateController::set_state(StateInterface *new_state)
{
    if (current_state != nullptr)
    {
        delete current_state;
        current_state = nullptr;
    }
    current_state = new_state;
}

void StateController::run()
{
    ir.get_command();
    current_state->run_display();
}

void StateController::on_notify_ir(uint16_t *ir_command)
{
    if (ir_command != nullptr)
    {
        current_state->ir_in(ir_command);
    }
}