#pragma once
#include "../Observers/IRObserver.h"
#include <list>

class IRSubject
{
public:
    virtual ~IRSubject() = default;
    void add_observer(IRObserver *observer) { observers.push_back(observer); }
    void remove_observer(IRObserver *observer) { observers.remove(observer); }
    virtual void notify_ir()
    {
        for (IRObserver *o : observers)
        {
            o->on_notify_ir();
        }
    }

protected:
    std::list<IRObserver *> observers;
};