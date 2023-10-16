#pragma once

class IRObserver
{
public:
    virtual ~IRObserver() = default;
    virtual void on_notify_ir() = 0;
};