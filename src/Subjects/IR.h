#pragma once
#include "IRSubject.h"

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>

#define IR_RECEIVER_PIN 4

#define IR_UP 0x18
#define IR_DOWN 0x52
#define IR_LEFT 0x8
#define IR_RIGHT 0x5a
#define IR_OK 0x1c
#define IR_STAR 0x16
#define IR_HASH 0xD
#define IR_1 0x45
#define IR_2 0x46
#define IR_3 0x47
#define IR_4 0x44
#define IR_5 0x40
#define IR_6 0x43
#define IR_7 0x7
#define IR_8 0x15
#define IR_9 0x9
#define IR_0 0x19

class IR : public IRSubject
{
public:
    IR();
    uint16_t *get_command();

private:
    IRrecv irrecv;
    IRData ir_data;
};