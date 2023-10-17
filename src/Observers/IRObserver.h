#pragma once

class IRObserver
{
public:
    virtual ~IRObserver() = default;
    virtual void on_notify_ir(uint16_t *ir_command) = 0;
};