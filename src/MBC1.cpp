#include "../include/MBC1.h"
#include <iostream>

MBC1::MBC1():
    romRAMMode(0),
    romBankNumberUpperBits(0)
{
    MBC::ramEnabled = false;
    MBC::currentROMBank = 0;
    MBC::currentRAMBank = 0;
}

MBC1::~MBC1()
{}

void MBC1::Update(u16 addr, u8 value)
{
    if(addr <= 0x1FFF)
        RAMEnable(value);
    else if(addr >= 0x2000 && addr <= 0x3FFF)
        SwitchROMBank(value);
    else if(addr >= 0x4000 && addr <= 0x5FFF)
    {
        if(romRAMMode == 0)
            SetROMBankNumberUpperBits(value);
        else
            RAMBankNumberSelect(value);
    }
    else
        ROMRAMModeSelect(value);
}

void MBC1::SwitchROMBank(u8 bank)
{
    /* 
     * When 0x00 is written, it is translated to 0x01.
     * The same goes for 0x20, 0x40 and 0x60.
     * These become 0x21, 0x41 and 0x61.
     */
    if(bank == 0 || bank == 0x20 || bank == 0x40 || bank == 0x60) 
    {
        MBC::currentROMBank++;
        return;
    }
    std::cout<<"switching rombank to: "<<std::hex<<(unsigned) bank<<std::endl;
    MBC::currentROMBank = (bank&0x1F) | ((romRAMMode == 0)?romBankNumberUpperBits<<5:0);
}

void MBC1::RAMEnable(u8 value)
{
    MBC::ramEnabled = (value == 0xA)?true:false;
}

void MBC1::ROMRAMModeSelect(u8 value)
{
    romRAMMode = value;
}

u8 MBC1::GetROMRAMMode(){return romRAMMode;}

void MBC1::RAMBankNumberSelect(u8 value)
{
    MBC::currentRAMBank = value;
}

void MBC1::SetROMBankNumberUpperBits(u8 value)
{
    romBankNumberUpperBits = value;
}
