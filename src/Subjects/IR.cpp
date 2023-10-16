#include "IR.h"

IR::IR() : irrecv(IR_RECEIVER_PIN)
{
    irrecv.enableIRIn();
}

uint16_t *IR::get_command()
{
    if (IrReceiver.decode())
    {
        this->ir_data = IrReceiver.decodedIRData;
        IrReceiver.resume();
        if (this->ir_data.flags & IRDATA_FLAGS_IS_REPEAT)
        {
            return nullptr;
        }
        return &this->ir_data.command;
    }
    else
    {
        return nullptr;
    }
}

void IR::notify_ir()
{
    for (IRObserver *o : observers)
    {
        o->on_notify_ir();
    }
}
