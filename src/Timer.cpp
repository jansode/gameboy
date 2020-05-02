#include "../include/Timer.h"
#include "../include/types.h"
#include "../include/CPU.h"
#include "../include/Memory.h"

#include <iostream>

Timer::Timer(CPU *cpu, Memory *memory):
    cpu(cpu),
    memory(memory),
    currFrequency(TIMA_FREQ0),
    timaCounter(0),
    divCounter(0),
    counter(0),
    divValue(0)
{}

void Timer::Tick(int cycles)
{
    /* 
     * The Divider Register(DIV) is incremented at a rate of 16384Hz. 
     * Any value written to this register resets it to 0.
     */ 
    counter+=cycles;

    divCounter = counter;
    if(divCounter >= (CPU_CLOCK_SPEED/DIVFREQ))
    {
        divCounter = 0;
        divValue++;

        /* Write would reset the counter */
        memory->GetMemory()[DIV_REGISTER] = (divValue&0xFF00)>>8;;  
    }
    
    /*
     * Check the third bit in the Timer Control(TAC)
     * register for a started timer.
     */
    if(memory->Read(TAC_REGISTER) & 4)
    {
        /*
         * The Timer Counter(TIMA) register is 
         * incremented at a frequency specified by 
         * the Timer Control(TAC) registers
         * first LS two bits. 
         */
        timaCounter = counter;

        if(timaCounter >= (CPU_CLOCK_SPEED/currFrequency))
        {
            timaCounter = 0;

            u8 timaValue = memory->Read(TIMA_REGISTER);
            
            /*
             * When the Timer Counter(TIMA) register overflows it loads 
             * the value in the Timer Modulo(TMA) register.
             */
            if(timaValue == 0)
            {
                /* Request timer interrupt */
                u8 interruptRequest = memory->Read(INTERRUPT_REQUEST_REGISTER);
                memory->Write(INTERRUPT_REQUEST_REGISTER, interruptRequest|CPU::TIMER_INTERRUPT);

                u8 tmaValue = memory->Read(TMA_REGISTER);
                memory->Write(TIMA_REGISTER, tmaValue);
            }
            else
            {
                memory->Write(TIMA_REGISTER, ++timaValue);
            }
        }
    }
}

void Timer::SetDIV(u16 value)
{
    divValue = value;
    memory->GetMemory()[DIV_REGISTER] = value;
}

void Timer::SetTIMA(u8 value)
{
    memory->GetMemory()[TIMA_REGISTER] = value;
}

void Timer::SetTIMAFrequency(u8 value)
{
    currFrequency = value;    
}
