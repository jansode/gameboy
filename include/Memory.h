#ifndef MEMORY_H
#define MEMORY_H

#include "definitions.h"
#include "types.h"
#include "memory_map.h"
#include "Cartridge.h"
#include "Timer.h"

class Joypad;

class Memory
{
    public:
        Memory(Joypad *joypad, Cartridge *cartridge, Timer *timer);
        void Init();
        u8 Read(u16 addr);
        void Write(u16 addr, u8 value);

        inline bool DMAActive(){return dmaActive;}

        void MemoryDump(u16 start, u16 end);
        void BootROMRemap();
        void DMATransfer(int cycles);
        u8 *GetMemory();

    private:
        u8          mmap[0x10000] = {0};

        Joypad*     joypad;
        Cartridge*  cartridge;
        Timer*      timer;

        bool        bootromDisabled;

        /* True if OAM DMA is running */
        bool        dmaActive;

        /* Keeps track of what OAM address offset needs to be written next. */
        int         currDMAIndex;

        /* The DMA source address. */
        u16         dmaAddress;
};
#endif
