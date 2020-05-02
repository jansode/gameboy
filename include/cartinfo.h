#ifndef CARTINFO_H
#define CARTINFO_H

namespace CartInfo
{
    const unsigned int CARTRIDGE_TITLE_LENGTH = 16;
    const unsigned int MAX_CARTRIDGE_ROM_SIZE = 0x100000;

    enum MBCType
    {
        ROMONLY,
        MBC1,
        MBC1_RAM,
        MBC1_RAM_BATTERY,
        MBC2,
        MBC2_BATTERY,
        ROM_RAM,
        ROM_RAM_BATTERY,
        MMM01,
        MMM01_RAM,
        MMM01_RAM_BATTERY,
        MBC3_TIMER_BATTERY,
        MBC3_TIMER_RAM_BATTERY,
        MBC3,
        MBC3_RAM,
        MBC3_RAM_BATTERY,
        MBC4,
        MBC4_RAM,
        MBC4_RAM_BATTERY,
        MBC5,
        MBC5_RAM,
        MBC5_RAM_BATTERY,
        MBC5_RUMBLE,
        MBC5_RUMBLE_RAM,
        MBC5_RUMBLE_RAM_BATTERY,
        POCKETCAMERA,
        BANDAITAMA5,
        HUC5,
        HUC1_RAM_BATTERY
    };

    enum ROMSize
    {
        ROM_KB32,
        ROM_KB64,
        ROM_KB128,
        ROM_KB256,
        ROM_KB512,
        ROM_MB1,
        ROM_MB2,
        ROM_MB4,
        ROM_MB8,
        ROM_MB1_1=0x52,
        ROM_MB1_2=0x53,
        ROM_MB1_5=0x54
    };

    enum RAMSize
    {
        RAM_NONE,
        RAM_KB2,
        RAM_KB8,
        RAM_KB32,
        RAM_KB128,
        RAM_KB64
    };

    enum Destination
    {
        JAPANESE,
        NON_JAPANESE,
        DESTINATION_NONE
    };
}
#endif
