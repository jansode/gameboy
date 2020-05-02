#ifndef OPERATIONS_H 
#define OPERATIONS_H 

void Load8BitReg(Reg8 &r1, Reg8 &r2);
void LoadImmediate8Bit(Reg8 &r, u8 value);
void LoadFromMemory8Bit(Reg8 &r, u16 addr);
void Load16BitReg(Reg16 &r1, Reg16 &r2);
void LoadImmediate16Bit(Reg16 &r1, u16 value);
void Add8BitReg(Reg8 &r1, Reg8 &r2, bool addCarry=false);
void Add8BitImmediate(Reg8 &r, u8 value, bool addCarry=false);
void Add16BitReg(Reg16 &r1, Reg16 &r2);
void Sub8BitReg(Reg8 &r1, Reg8 &r2, bool addCarry=false);
void Sub8BitImmediate(Reg8 &r, u8 value, bool addCarry=false);
void AND8BitReg(Reg8 &r1, Reg8 &r2);
void AND8BitImmediate(Reg8 &r1, u8 value);
void OR8BitReg(Reg8 &r1, Reg8 &r2);
void OR8BitImmediate(Reg8 &r1, u8 value);
void XOR8BitReg(Reg8 &r1, Reg8 &r2);
void XOR8BitImmediate(Reg8 &r1, u8 value);
void SwapNibblesReg(Reg8 &r);
void SwapNibblesImmediate(u8 *value);

void Test8BitRegBit(Reg8 &r, u8 bit);
void TestMemoryBit(u16 addr, u8 bit);

void Set8BitRegBit(Reg8 &r, u8 bit);
void SetMemoryBit(u16 addr, u8 bit);

void Jump8BitImmediate(bool condition=true);
void Jump16BitImmediate();
void JumpToAddress(u16 address);

void Increment8BitReg(Reg8 &r);
void Increment16BitReg(Reg16 &r);
void IncrementAddress(u16 addr);

void Decrement8BitReg(Reg8 &r);
void DecrementAddress(u16 addr);

void Rotate8BitRegLeft(Reg8 &r, bool throughCarry=true);
void RotateAddressLeft(u16 addr, bool throughCarry);

void Rotate8BitRegRight(Reg8 &r, bool troughCarry=true);
void RotateAddressRight(u16 addr, bool throughCarry);

void Shift8BitRegRightIntoCarry(Reg8 &r, bool clearMSB=false);
void Shift8BitRegLeftIntoCarry(Reg8 &r);

void ShiftAddressLeftIntoCarry(u16 addr);
void ShiftAddressRightIntoCarry(u16 addr, bool clearMSB);

void Compare8BitReg(Reg8 &r1, Reg8 &r2);
void Compare8BitImmediate(Reg8 &r, u8 value);
void CompareAddress(Reg8 &r1, u16 addr);

void ResetRegisterBit(Reg8 &r, u8 bit);
void ResetMemoryBit(u16 addr, u8 bit);

void Call();
void Return();

void PushStack(u16 value);
u16 PopStack();

void SetZeroFlagFromResult(u8 result);

#endif
