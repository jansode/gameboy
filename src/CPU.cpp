#include "../include/CPU.h"
#include <iostream>
#include <iomanip>

#include "../include/definitions.h"

CPU::CPU(Memory *memory):
    memory(memory),
    interruptMasterEnableFlag(false),
    disableInterruptsCounter(0),
    enableInterruptsCounter(0),
    booted(false),
    halted(false),
    haltUntilButtonPress(false)
{
}

void CPU::Init()
{
    /*
     * Values according to 
     * http://bgb.bircd.org/pandocs.htm#powerupsequence
     */
    regAF.value = 0x01B0;
    regBC.value = 0x0013;
    regDE.value = 0x00D8;
    regHL.value = 0x014D;
    regSP.value = 0xFFFE;
    regPC.value = 0;
}

void CPU::SetFlags(u8 mask)
{
    regF = (regF | mask);
}

void CPU::ClearFlags(u8 mask)
{
    regF = regF & ~mask;
}

void CPU::ClearAllFlags()
{
    regF = 0;
}

u8 CPU::Get8BitRegisterValue(const std::string &reg)
{
    if(reg == "A") return regA;
    else if(reg == "F") return regF;
    else if(reg == "B") return regB;
    else if(reg == "C") return regC;
    else if(reg == "D") return regD;
    else if(reg == "E") return regE;
    else if(reg == "H") return regH;
    else if(reg == "L") return regL;
    else return 0x0; 
}

void CPU::PrintRegisters()
{
    std::cout<<"PC: "<<std::hex<<(unsigned)regPC.value<<std::endl;
    std::cout<<"SP: "<<std::hex<<(unsigned)regSP.value<<std::endl;
    
    std::cout<<"A: "<<std::hex<<(unsigned)regA<<std::endl;
    std::cout<<"F: "<<std::hex<<(unsigned)regF<<std::endl;
    std::cout<<"B: "<<std::hex<<(unsigned)regB<<std::endl;
    std::cout<<"C: "<<std::hex<<(unsigned)regC<<std::endl;
    std::cout<<"D: "<<std::hex<<(unsigned)regD<<std::endl;
    std::cout<<"E: "<<std::hex<<(unsigned)regE<<std::endl;
    std::cout<<"H: "<<std::hex<<(unsigned)regH<<std::endl;
    std::cout<<"L: "<<std::hex<<(unsigned)regL<<std::endl;
}

void CPU::PrintStack(u8 bytes)
{
    memory->MemoryDump(regSP.value,regSP.value+bytes);
}

bool CPU::FlagSet(u8 flag)
{
    return ((flag & regF) > 0);

}

bool CPU::FlagCleared(u8 flag)
{
    return ((flag & regF) == 0);
}

void CPU::InterruptEnableCheck()
{
    if(enableInterruptsCounter > 0)
    {
        if(enableInterruptsCounter == 1)
            interruptMasterEnableFlag = true;

        --enableInterruptsCounter;
    }
}

void CPU::InterruptDisableCheck() 
{
    if(disableInterruptsCounter > 0)
    {
        if(disableInterruptsCounter == 1)
            interruptMasterEnableFlag = false;

        --disableInterruptsCounter;
    }
}

void CPU::InterruptRequest(int interrupt)
{
    u8 bits = memory->Read(INTERRUPT_REQUEST_REGISTER); 
    bits |= interrupt;
    memory->Write(INTERRUPT_REQUEST_REGISTER,bits);
}

void CPU::CheckInterrupts()
{
    InterruptEnableCheck();
    InterruptDisableCheck();
    if(interruptMasterEnableFlag)
    {
        u8 requestBits = memory->Read(INTERRUPT_REQUEST_REGISTER);
        u8 enabledBits = memory->Read(INTERRUPT_ENABLED_REGISTER);

        if(requestBits > 0)
        {
            /* The interrupts need to be checked in order of their priority. */
            for(int i=0; i<5; ++i) 
            {
                u8 interrupt = (1<<i);

                /* Is interrupt requested? */
                if(!((requestBits & interrupt) > 0)) continue;

                /* Is interrupt enabled? */
                if(!((enabledBits & interrupt) > 0)) continue;
                

                /* Get out of halted state when an interrupt occurs. */
                if(halted)
                {
                    halted = false;
                    regPC.value++;
                }
                
                ServiceInterrupt(interrupt);

            }
        }
    }

    /*
     * If halted and interrupts are disabled,
     * the next instruction is skipped.
     * source: http://www.devrs.com/gb/files/gbspec.txt 
     */
    /*
    if(halted && !interruptMasterEnableFlag) 
    {
        halted = false;
        regPC.value++;
        return;
    }
    */
}


void CPU::ServiceInterrupt(int interrupt)
{
    /* Reset the IME flag and the bit in the IR register. */
    interruptMasterEnableFlag = false; 
    u8 requestBits = memory->Read(INTERRUPT_REQUEST_REGISTER);
    requestBits &= ~interrupt;
    memory->Write(INTERRUPT_REQUEST_REGISTER,requestBits);

    /*
     * Push the current value of the program counter on the stack
     * so that we can return to this address after the interrupt finishes.
     */
    PushStack(regPC.value); 

    /*
     * Set the program counter to the starting address of the 
     * interrupt service routine.
     */
    switch(interrupt)
    {
        case VBLANK_INTERRUPT:
            regPC.value = VBLANK_SERVICE_ROUTINE;
            break;
        case LCD_INTERRUPT:
            regPC.value = LCD_SERVICE_ROUTINE;
            break;
        case TIMER_INTERRUPT:
            regPC.value = TIMER_SERVICE_ROUTINE;
            break;
        case SERIAL_INTERRUPT:
            regPC.value = SERIAL_SERVICE_ROUTINE;
            break;
        case JOYPAD_INTERRUPT:
            regPC.value = JOYPAD_SERVICE_ROUTINE;
            break;
        default:
            std::cerr<<"Undefined interrupt requested: "<<std::hex<<(unsigned)interrupt<<std::endl;
            break;
    }
}

u8 CPU::Fetch()
{
    u8 opcode = memory->Read(regPC.value);
    return opcode;
}

int CPU::Execute(u8 opcode)
{
    switch(opcode)
    {
        #include "../include/opcodes.h"
    }
}
