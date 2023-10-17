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
        notify_ir(&ir_data.command);
        return &ir_data.command;
    }
    else
    {
        return nullptr;
    }
}
