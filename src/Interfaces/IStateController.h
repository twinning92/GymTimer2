#pragma once

class StateInterface;

class IStateController
{
public:
    virtual void set_state(StateInterface *new_state) = 0;
    virtual ~IStateController() = default;
};