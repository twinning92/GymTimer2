#pragma once

class TimeObserver
{
public:
    virtual ~TimeObserver() = default;
    virtual void on_notify_second() = 0;
};