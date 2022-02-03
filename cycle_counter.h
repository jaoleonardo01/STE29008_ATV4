#ifndef __CYCLE_COUNTER_H__
#define __CYCLE_COUNTER_H__

class Cycle_Counter
{
private:
    /* data */
public:
    Cycle_Counter();
    ~Cycle_Counter();

    void start() __attribute__((always_inline));
    unsigned char stop() __attribute__((always_inline));
};

inline void Cycle_Counter::start()
{
    asm (
        "clr r1\n\t"
        "cli\n\t"
        "ldi r30, 0xb2\r\n"
        "ldi r31, 0x00\r\n"
        "st  Z, r1\r\n"   // TCNT2 = 0
    );
}

inline unsigned char Cycle_Counter::stop()
{
    unsigned char ncycles;
    asm (
        "ldi r30, 0xb2\r\n"
        "ldi r31, 0x00\r\n"
        "ld %0, Z\n\t"
        "sei\n\t"
        : "=r" (ncycles)
        :
    );
    return ncycles - 3;
}

#endif // __CYCLE_COUNTER_H__