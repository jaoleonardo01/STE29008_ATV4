#include "cycle_counter.h"

Cycle_Counter::Cycle_Counter(/* args */)
{
    asm (
        "clr r1\n\t"
        "clr r0\n\t"
        "inc r0\n\t"
        "ldi r30, 0xb0\r\n"
        "ldi r31, 0x00\r\n"
        "st  Z+, r1\r\n"
        "st  Z, r0\r\n"
    );
}

Cycle_Counter::~Cycle_Counter()
{
}
