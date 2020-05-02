#ifndef MBC1_H
#define MBC1_H

#include "MBC.h"

class MBC1 : public MBC
{
    public:
        MBC1();
        ~MBC1();

        void Update(u16 addr, u8 value);

        void SwitchROMBank(u8 bank);
        void RAMEnable(u8 value);
        void ROMRAMModeSelect(u8 value);
        void RAMBankNumberSelect(u8 value);
        void SetROMBankNumberUpperBits(u8 value);
        u8 GetROMRAMMode();
    private:
        bool    ramEnabled;
        u8      romRAMMode;
        u8      romBankNumberUpperBits;
}; 

#endif
