#ifndef TIMER_H
#define TIMER_H

#include "types.h"

class CPU;
class Memory;

class Timer
{
    public:
        enum Frequency
        {
            TIMA_FREQ0=4096,
            TIMA_FREQ1=262144,
            TIMA_FREQ2=65536,
            TIMA_FREQ3=16384,
            DIVFREQ=32768,
        };

        Timer(CPU *cpu, Memory *memory);
        void Tick(int cycles);

        void SetDIV(u16 value);
        void SetTIMA(u8 value);
        void SetTIMAFrequency(u8 value);

    private:
        CPU*        cpu;  
        Memory*     memory;
        unsigned    currFrequency;
        unsigned    timaCounter;
        unsigned    divCounter;
        unsigned    counter;
        u16         divValue;
};

#endif
