#ifndef CPU_H
#define CPU_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Memory.h"

typedef u8 Reg8;

union Reg16
{
    u16 value;

    struct
    {
        Reg8 low;
        Reg8 high;
    };
};

class CPU
{
    public:
        enum Flags
        {
            ZERO       =0x80,
            ADDSUB     =0x40,
            HALFCARRY  =0x20,
            CARRY      =0x10,
        };

        enum Interrupts
        {
            VBLANK_INTERRUPT    =0x1,
            LCD_INTERRUPT       =0x2,
            TIMER_INTERRUPT     =0x4,
            SERIAL_INTERRUPT    =0x8,
            JOYPAD_INTERRUPT    =0x10 
        };

       CPU(Memory *memory);
       void Init();

       /*
        * Fetch the next instruction from memory.
        */
       u8 Fetch();

       /*
        * Executes the given opcode.
        * Returns the amount of cycles taken.
        */
       int Execute(u8 opcode);

       #include "operations.h"

       /*
        * Sets the bits in the flags register
        * indicated by the mask
        */
       void SetFlags(u8 mask);

       /*
        * Clears the bits in the flags register
        * indicated by the mask
        */
       void ClearFlags(u8 mask);

       /*
        * Clears all the bits in the flags register
        */
       void ClearAllFlags();

       /*
        * Returns true if the specified flag
        * is set in the flags register
        */
       bool FlagSet(u8 flag);

       /*
        * Returns true if the specified flag
        * is not set in the flags register.
        */
       bool FlagCleared(u8 flag);


       void PrintRegisters();

       /*
        * Requests an interrupt.
        * Sets the bit corresponding to this
        * interrupt in the IR register.
        *
        */
       void InterruptRequest(int interrupt);

       /*
        * Checks the IME, IR and IE registers.
        * If interrupt is requested and enabled,
        * run the interrupt service routine for this
        * interrupt.
        * 
        */
       void CheckInterrupts();

       /*
        * Runs the interrupt service routine for the
        * given interrupt
        *
        */
       void ServiceInterrupt(int interrupt);

       void InterruptDisableCheck();
       void InterruptEnableCheck();

       inline bool IsHaltedUntilButtonPress(){return haltUntilButtonPress;}
       inline bool IsHalted(){return halted;}

       inline u16 GetCurrentAddress(){return regPC.value;}

       inline u8 GetNextInstruction(){return memory->Read(regPC.value);}
       inline u8 getAValue(){return regA;}

       void PrintStack(u8 bytes);
       void PrintCallStack();
       void PrintStackSize();
       u8 Get8BitRegisterValue(const std::string &reg);

    private:


       /* combined 16-bit registers */
       Reg16 regAF; 
       Reg16 regBC;
       Reg16 regDE;
       Reg16 regHL;

       /* 8-bit registers */
       Reg8& regA = regAF.high; 
       Reg8& regF = regAF.low; 
       Reg8& regB = regBC.high;
       Reg8& regC = regBC.low;
       Reg8& regD = regDE.high;
       Reg8& regE = regDE.low;
       Reg8& regH = regHL.high;
       Reg8& regL = regHL.low;

       /* Stack Pointer */
       Reg16 regSP; 

       /* Program Counter */
       Reg16 regPC; 

       Memory *memory;


       /*
        * The IME flag is used to disable all interrupts.
        * This overrides the IE register bits. 
        */
       bool interruptMasterEnableFlag;


       /*
        * The DI instruction uses this to disable interrupts 
        * after the instruction after it.
        */
       u8 disableInterruptsCounter;

       /*
        * The EI instruction uses this to enable interrupts 
        * after the instruction after it.
        */
       u8 enableInterruptsCounter;

       bool booted;

       bool halted;

       /* For STOP instruction */
       bool haltUntilButtonPress;
};
#endif
