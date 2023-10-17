#pragma once
#include "../Observers/TimeObserver.h"
#include <list>

class TimeSubject
{
public:
    virtual ~TimeSubject() = default;
    void add_observer(TimeObserver *observer) { observers.push_back(observer); }
    void remove_observer(TimeObserver *observer) { observers.remove(observer); }
    virtual void notify_second()
    {
        for (TimeObserver *o : observers)
        {
            o->on_notify_second();
        }
    }

protected:
    std::list<TimeObserver *> observers;
};