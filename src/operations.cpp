#include "../include/CPU.h"
#include <iostream>
#include <assert.h>

void CPU::Load16BitReg(Reg16 &r1, Reg16 &r2)
{
    r1.value = r2.value;
}

void CPU::LoadImmediate16Bit(Reg16 &r1, u16 value)
{
    r1.value = value;
}

void CPU::LoadFromMemory8Bit(Reg8 &r, u16 addr)
{
    u8 value = memory->Read(addr);
    LoadImmediate8Bit(r,value);
}

void CPU::Add8BitReg(Reg8 &r1, Reg8 &r2, bool addCarry)
{
   u8 r1Value = r1;
   u8 r2Value = r2;

   u16 result = r1Value+r2Value;

   ClearFlags(ADDSUB);

   if(addCarry && FlagSet(CARRY)) result++;

   SetZeroFlagFromResult(result);

   if(((result ^ r1Value ^ r2Value) & 0x100) == 0x100)
       SetFlags(CARRY);
   else
       ClearFlags(CARRY);

   if(((result ^ r1Value ^ r2Value) & 0x10) == 0x10)
       SetFlags(HALFCARRY);
   else
       ClearFlags(HALFCARRY);

   r1=result;
}

void CPU::Add8BitImmediate(Reg8 &r, u8 value, bool addCarry)
{
   u8 regVal = r;
   u16 result = regVal + value;
   u8 carry = (FlagSet(CARRY))?1:0;

   if(addCarry) result+=carry;

   SetZeroFlagFromResult(result);

   ClearFlags(ADDSUB);

   if(((result ^ regVal ^ value) & 0x100) == 0x100)
   {
       SetFlags(CARRY);
   }
   else
       ClearFlags(CARRY);
   if(((result ^ regVal ^ value) & 0x10) == 0x10)
       SetFlags(HALFCARRY);
   else
       ClearFlags(HALFCARRY);

   r=result;
}

void CPU::Sub8BitReg(Reg8 &r1, Reg8 &r2, bool addCarry)
{
    u8 reg1Val = r1;
    u8 reg2Val = r2;
    u8 result = reg1Val - reg2Val; 
    u8 carry = (FlagSet(CARRY))?1:0;

    if(addCarry) result-=carry;
    else carry=0;

    SetZeroFlagFromResult(result);

    SetFlags(ADDSUB);

    if(reg1Val < (reg2Val+carry)) 
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);

    if(((s16)(reg1Val & 0xF) - (reg2Val & 0xF) - carry) < 0)
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    r1=result;
}

void CPU::Sub8BitImmediate(Reg8 &r, u8 value, bool addCarry)
{
    u8 regVal = r;
    u8 carry = (FlagSet(CARRY))?1:0;
    u8 result;
    if(addCarry)
    {
        result = regVal - (value + carry);
    }
    else
    {
        result = regVal - value;
        carry=0;
    }


    SetZeroFlagFromResult(result);

    SetFlags(ADDSUB);

    if(regVal < ((u16)value+carry))
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);

    if((regVal & 0xF) < ((value & 0xF)+carry))
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    r=result;
}

void CPU::AND8BitReg(Reg8 &r1, Reg8 &r2)
{
    u8 reg1Val = r1;
    u8 reg2Val = r2;
    u8 result = reg1Val & reg2Val;

    SetZeroFlagFromResult(result);

    SetFlags(HALFCARRY);

    ClearFlags(ADDSUB|CARRY);

    r1=result;
}


void CPU::AND8BitImmediate(Reg8 &r1, u8 value)
{
    u8 reg1Val = r1;
    u8 result = reg1Val & value;

    SetZeroFlagFromResult(result);

    SetFlags(HALFCARRY);

    ClearFlags(ADDSUB|CARRY);

    r1=result;
}

void CPU::Add16BitReg(Reg16 &r1, Reg16 &r2)
{
   u16 r1Value = r1.value;
   u16 r2Value = r2.value;
   u32 result = r1Value+r2Value;

   ClearFlags(ADDSUB);

   if(result > 0xFFFF)
       SetFlags(CARRY);
   else
       ClearFlags(CARRY);

   if((result&0xFFF) < (r1Value&0xFFF))
       SetFlags(HALFCARRY);
   else
       ClearFlags(HALFCARRY);

   r1.value = (u16)result;
}

void CPU::OR8BitReg(Reg8 &r1, Reg8 &r2)
{
    u8 reg1Val = r1;
    u8 reg2Val = r2;
    u8 result = reg1Val | reg2Val;

    SetZeroFlagFromResult(result);

    ClearFlags(HALFCARRY|ADDSUB|CARRY);

    r1=result;
}

void CPU::OR8BitImmediate(Reg8 &r1, u8 value)
{
    u8 reg1Val = r1;
    u8 result = reg1Val | value;

    SetZeroFlagFromResult(result);

    ClearFlags(HALFCARRY|ADDSUB|CARRY);

    r1=result;
}

void CPU::XOR8BitReg(Reg8 &r1, Reg8 &r2)
{
    u8 reg1Val = r1;
    u8 reg2Val = r2;
    u8 result = reg1Val ^ reg2Val;

    SetZeroFlagFromResult(result);

    ClearFlags(HALFCARRY|ADDSUB|CARRY);

    r1=result;
}


void CPU::XOR8BitImmediate(Reg8 &r1, u8 value)
{
    u8 reg1Val = r1;
    u8 result = reg1Val ^ value;

    SetZeroFlagFromResult(result);

    ClearFlags(HALFCARRY|ADDSUB|CARRY);

    r1=result;
}

void CPU::SwapNibblesReg(Reg8 &r)
{
    u8 value = r;
    u8 high = 0xF0 & value;
    u8 low  = 0x0F & value;
    u8 result = (low << 4) | (high >> 4);

    SetZeroFlagFromResult(result);

    ClearFlags(ADDSUB|HALFCARRY|CARRY);

    r=result;
}

void CPU::SwapNibblesImmediate(u8 *value)
{
    u8 high = 0xF0 & *value;
    u8 low  = 0x0F & *value;
    *value = (low << 4) | (high >> 4);

    SetZeroFlagFromResult(*value);

    ClearFlags(ADDSUB|HALFCARRY|CARRY);
}

void CPU::Compare8BitReg(Reg8 &r1, Reg8 &r2)
{
    u8 reg1Val = r1;
    u8 reg2Val = r2;

    if(reg1Val == reg2Val)
        SetFlags(ZERO);
    else
        ClearFlags(ZERO);

    SetFlags(ADDSUB);

    if(((reg1Val-reg2Val)& 0x0F) > (reg1Val&0x0F))
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    if(reg1Val < reg2Val)
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);
}

void CPU::Compare8BitImmediate(Reg8 &r1, u8 value)
{
    u8 reg1Val = r1;
    u8 reg2Val = value;

    if(reg1Val == reg2Val)
        SetFlags(ZERO);
    else
        ClearFlags(ZERO);

    SetFlags(ADDSUB);

    if(((reg1Val-reg2Val)&0xF) > (reg1Val&0xF))
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    if(reg1Val < reg2Val)
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);
}

void CPU::CompareAddress(Reg8 &r1, u16 addr)
{
    u8 reg1Val = r1;
    u8 reg2Val = memory->Read(addr);

    if(reg1Val == reg2Val)
        SetFlags(ZERO);
    else
        ClearFlags(ZERO);

    SetFlags(ADDSUB);

    if(((reg1Val-reg2Val)& 0x0F) > (reg1Val&0x0F))
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    if(reg1Val < reg2Val)
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);
}



void CPU::Load8BitReg(Reg8 &r1, Reg8 &r2) 
{
    r1=r2;
}

void CPU::LoadImmediate8Bit(Reg8 &r, u8 value)
{
    r = value;
}

void CPU::Rotate8BitRegLeft(Reg8 &r, bool throughCarry)
{
    ClearFlags(ADDSUB|HALFCARRY);

    u8 result;
    if(throughCarry)
    {
        u8 oldCarry = (FlagSet(CARRY))?1:0;
        if((r & 0x80))
            SetFlags(CARRY);
        else
            ClearFlags(CARRY);

        u8 regVal= r;
        result = (regVal<<1)|oldCarry;
    }
    else
    {
        if((r & 0x80))
            SetFlags(CARRY);
        else
            ClearFlags(CARRY);

        u8 regVal = r;
        u8 old = regVal & 0x80;
        result = (regVal << 1) | old >> 7;
    }

    SetZeroFlagFromResult(result);

    r=result;
}

void CPU::Rotate8BitRegRight(Reg8 &r, bool throughCarry)
{
    ClearFlags(ADDSUB|HALFCARRY);

    u8 result;
    if(throughCarry)
    {
        u8 oldCarry = (FlagSet(CARRY))?0x80:0;
        if(r & 0x1)
            SetFlags(CARRY);
        else
            ClearFlags(CARRY);

        u8 regVal = r;
        result = (regVal>>1)|oldCarry;
    }
    else
    {
        if((r & 0x1))
            SetFlags(CARRY);
        else
            ClearFlags(CARRY);

        u8 regVal = r;
        u8 old = regVal & 1;
        result = (regVal>>1) | (old << 7);
    }

    SetZeroFlagFromResult(result);

    r=result;
}

void CPU::RotateAddressRight(u16 addr, bool throughCarry)
{
    ClearFlags(ADDSUB|HALFCARRY);
    u8 addrVal = memory->Read(addr);
    u8 bitZero = addrVal & 1;

    u8 result;
    if(throughCarry)
    {
        u8 oldCarry = (FlagSet(CARRY))?0x80:0;
        result = (addrVal>>1)|oldCarry;
    }
    else
        result = (addrVal>>1)|(bitZero<<7);

    if(bitZero)
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);

    SetZeroFlagFromResult(result);

    memory->Write(addr,result);
}

void CPU::RotateAddressLeft(u16 addr, bool throughCarry)
{
    ClearFlags(ADDSUB|HALFCARRY);

    u8 addrVal = memory->Read(addr);
    u8 bitSeven = addrVal & 0x80;

    u8 result;
    if(throughCarry)
    {
        u8 oldCarry = (FlagSet(CARRY))?1:0;
        result = (addrVal<<1)|oldCarry;
    }
    else
        result = (addrVal<<1)|(bitSeven>>7);

    if(bitSeven)
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);

    SetZeroFlagFromResult(result);

    memory->Write(addr,result);
}

void CPU::Jump8BitImmediate(bool condition)
{
    s8 value = (s8)memory->Read(regPC.value+1);
    if(condition)
        regPC.value+=value;
}

void CPU::Jump16BitImmediate()
{
    u8 low = memory->Read(regPC.value+1);
    u8 high = memory->Read(regPC.value+2);

    regPC.value = (((u16)high << 8) | low);
}

void CPU::JumpToAddress(u16 address)
{
    regPC.value=address;
}

void CPU::Increment8BitReg(Reg8 &r)
{
    u8 curr_val = r;
    u8 result = curr_val+1;

    SetZeroFlagFromResult(result);

    ClearFlags(ADDSUB);

    if((result & 0xF) == 0)
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    r=result;
}

void CPU::Increment16BitReg(Reg16 &r)
{
    r.value++;
}

void CPU::IncrementAddress(u16 addr)
{
    u8 currVal = memory->Read(addr);
    u8 result = currVal+1;

    SetZeroFlagFromResult(result);

    ClearFlags(ADDSUB);

    if((result & 0xF) == 0)
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    memory->Write(addr,result);
}

void CPU::Decrement8BitReg(Reg8 &r)
{
    u8 regVal = r; 
    u8 result = --regVal;

    SetZeroFlagFromResult(result);

    SetFlags(ADDSUB);

    if((result & 0x0F) == 0x0F)
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    r=result;
}

void CPU::DecrementAddress(u16 addr)
{
    u8 addrVal = memory->Read(addr); 
    u8 result = --addrVal;

    SetZeroFlagFromResult(result);

    SetFlags(ADDSUB);

    if((result & 0x0F) == 0x0F)
        SetFlags(HALFCARRY);
    else
        ClearFlags(HALFCARRY);

    memory->Write(addr,result);
}

void CPU::Test8BitRegBit(Reg8 &r, u8 bit)
{
    u8 regVal = r;

    ClearFlags(ADDSUB);

    if((regVal & (1<<bit)) == 0) SetFlags(ZERO);
    else ClearFlags(ZERO);

    SetFlags(HALFCARRY);
}

void CPU::TestMemoryBit(u16 addr, u8 bit)
{
    u8 value = memory->Read(addr);

    ClearFlags(ADDSUB);

    if((value & (1<<bit)) == 0) SetFlags(ZERO);
    else ClearFlags(ZERO);

    SetFlags(HALFCARRY);
}

void CPU::Shift8BitRegRightIntoCarry(Reg8 &r, bool clearMSB)
{
    u8 value = r;
    ((value & 0x1))?SetFlags(CARRY):ClearFlags(CARRY);

    if(clearMSB) value >>= 1;
    else
    {
        value >>= 1;
        if((value & 0x80)) value|=0x80;
    }

    if(value == 0) SetFlags(ZERO);
    else ClearFlags(ZERO);

    ClearFlags(ADDSUB|HALFCARRY);

    r = value;
}

void CPU::Shift8BitRegLeftIntoCarry(Reg8 &r)
{
    u8 value = r;
    if((value & 0x80))
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);

    value <<= 1;

    if(value == 0) SetFlags(ZERO);

    ClearFlags(ADDSUB|HALFCARRY);

    r = value;
}

void CPU::ShiftAddressLeftIntoCarry(u16 addr)
{
    u8 value = memory->Read(addr);
    if((value & 0x80))
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);

    value <<= 1;

    SetZeroFlagFromResult(value);
    ClearFlags(ADDSUB|HALFCARRY);

    memory->Write(addr,value);
}

void CPU::ShiftAddressRightIntoCarry(u16 addr, bool clearMSB)
{
    u8 value = memory->Read(addr);
    if((value & 1))
        SetFlags(CARRY);
    else
        ClearFlags(CARRY);

    if(clearMSB)
        value >>= 1;
    else
    {
        u8 MSB = value & 0x80;
        value = (value >> 1) | MSB;
    }

    SetZeroFlagFromResult(value);
    ClearFlags(ADDSUB|HALFCARRY);

    memory->Write(addr,value);
}

void CPU::ResetRegisterBit(Reg8 &r, u8 bit)
{
    u8 regVal = r;
    u8 result = regVal & ~(1<<bit);
    r=result;
}

void CPU::ResetMemoryBit(u16 addr, u8 bit)
{
    u8 value = memory->Read(addr);
    u8 result = value & ~(1<<bit);
    memory->Write(addr,result);
}

void CPU::Set8BitRegBit(Reg8 &r, u8 bit)
{
    u8 value = r; 

    value |= (1 << bit);
    r = value;
}

void CPU::SetMemoryBit(u16 addr, u8 bit)
{
    u8 value = memory->Read(addr);
    value |= (1 << bit);
    memory->Write(addr, value);
}

void CPU::Call()
{
    PushStack(regPC.value+3);
    u16 address = memory->Read(regPC.value+2)<<8|(memory->Read(regPC.value+1));
    regPC.value=address;
}

void CPU::Return()
{
    u16 address = PopStack();    
    regPC.value=address;
}

void CPU::PushStack(u16 value)
{
    regSP.value--;

    u8 low = (u8) value & 0xFF;
    u8 high = (u8) ((value & 0xFF00) >> 8);

    memory->Write(regSP.value,high);

    regSP.value--;
    memory->Write(regSP.value,low);
}

u16 CPU::PopStack()
{
    u8 low = memory->Read(regSP.value);
    regSP.value++;

    u8 high = memory->Read(regSP.value);
    regSP.value++;

    return ((u16)high << 8) | low;
}

void CPU::SetZeroFlagFromResult(u8 result)
{
    if(result == 0) 
        SetFlags(ZERO);
    else 
        ClearFlags(ZERO);
}

