#include "../include/Memory.h"
#include "../include/Joypad.h"
#include "../include/boot_rom.h"
#include "../include/cartinfo.h"
#include <iostream>
#include <iomanip>

Memory::Memory(Joypad *joypad, Cartridge *cartridge, Timer *timer):
    joypad(joypad),
    cartridge(cartridge),
    timer(timer),
    bootromDisabled(false),
    dmaActive(false),
    currDMAIndex(0),
    dmaAddress(0)
{}

void Memory::Init()
{
    /* Load the boot ROM */
    for(int i=0;i<256;++i) mmap[i] = boot_rom[i];

    u8 *cartridge_memory = cartridge->GetROM();

    /* Initialize ROM bank 00 and 01 from cartridge */
    for(int i=MM_ROM_BANK00_START+0x100;i<=MM_ROM_BANK_SWITCHABLE_END;++i)
        mmap[i] = cartridge_memory[i];

    /*
     * Values according to
     * http://bgb.bircd.org/pandocs.htm#powerupsequence
     */
    mmap[JOYPAD_REGISTER] = 0xCF;

    mmap[0xFF05] = 0;
    mmap[0xFF06] = 0;
    mmap[0xFF07] = 0;
    mmap[0xFF10] = 0x80;
    mmap[0xFF11] = 0xBF;
    mmap[0xFF12] = 0xF3;
    mmap[0xFF14] = 0xBF;
    mmap[0xFF16] = 0x3F;
    mmap[0xFF19] = 0xBF;
    mmap[0xFF1A] = 0x7F;
    mmap[0xFF1B] = 0xFF;
    mmap[0xFF1C] = 0x9F;
    mmap[0xFF1E] = 0xBF;
    mmap[0xFF20] = 0xFF;
    mmap[0xFF23] = 0xBF;
    mmap[0xFF24] = 0x77;
    mmap[0xFF25] = 0xF3;
    mmap[0xFF26] = 0xF3; 
    mmap[0xFF40] = 0x91;
    mmap[0xFF47] = 0xFC;
    mmap[0xFF48] = 0xFF;
    mmap[0xFF49] = 0xFF;
    mmap[0xFF4A] = 0;
    mmap[0xFF4B] = 0;
    mmap[0xFFFF] = 0;
    
}

u8 Memory::Read(u16 addr)
{
    /* Get joypad state */
    if(addr == JOYPAD_REGISTER)
    {
        return joypad->GetState();
    }
    /* Read from switchable ROM bank */
    else if(cartridge->HasMBC() && addr >= MM_ROM_BANK_SWITCHABLE_START && addr <= MM_ROM_BANK_SWITCHABLE_END) 
    {
        return cartridge->Read(addr);
    }
    else
    {
        return mmap[addr];
    }
}

void Memory::Write(u16 addr, u8 value)
{
    /* Writes during OAM DMA transfer are ignored except to the DMA register. */
    if(dmaActive && addr != DMA_TRANSFER_ADDRESS) return;

    /* Read only memory */
    if(addr < 0x8000)
    {
        if(cartridge->HasMBC())
        {
            cartridge->UpdateMBC(addr,value);
        }
        else
        {
            mmap[addr] = value;
        }
    }

    /* Not usable memory */
    else if((addr >= 0xFEA0) && (addr < 0xFEFF))
    {
    }

    /* Writing to these addresses sets them to 0 */
    else if(addr == LY_ADDRESS)
    {
        mmap[addr] = 0;
    }
    /* Writing to the DIV register resets 
     * both the DIV register and the 
     * timer register
     */
    else if(addr == DIV_REGISTER)
    {
        timer->SetDIV(0);
        timer->SetTIMA(0);
    }

    /*
     * Update timer frequency
     */
    else if(addr == TAC_REGISTER)
    {
        timer->SetTIMAFrequency(value&3);
    }

    /*
     * Writing to this address launches a DMA transfer
     * from ROM or RAM to OAM memory
     */
    else if(addr == DMA_TRANSFER_ADDRESS) 
    {
        /*
         * The written value specifies the transfer
         * source address divided by 0x100 
         */
        dmaAddress = value * 0x100;
        dmaActive = true;
        currDMAIndex = 0;
    }
    /*
     * Writing 1 to this register disables the
     * boot ROM and remaps the first 256 bytes 
     * to the cartridge bank00.
     */
    else if(addr == DISABLE_BOOT_ROM_REGISTER)
    {
        if(!bootromDisabled && value == 1)
        {
            bootromDisabled = true;
            mmap[DISABLE_BOOT_ROM_REGISTER] = 1;
            BootROMRemap(); 
        }
    }
    else
    {
        mmap[addr] = value;
    }
}

void Memory::MemoryDump(u16 start, u16 end)
{
    std::cout<<"0x"<<std::hex<<start<<"\t";

    unsigned linecount = 0,linestart=start;
    for(int i=start;i<end;++i,++linecount)
    {
            if(linecount == 15)
            {
                std::cout<<"|";
                for(unsigned j=linestart; j<linestart+0xF; ++j)
                {
                    std::cout<<(char)((Read(j) >= 33 && Read(j) <= 126)?Read(j):'.');    
                }
                std::cout<<"|";

                linestart = i+1;
                linecount = 0;
                std::cout<<"\n";
                std::cout<<"0x"<<std::hex<<(int)i<<"\t";
            }
            std::cout<<std::hex<<std::setfill('0')<<std::setw(2)<<(int)(Read(i))<<" ";
    }
    std::cout<<std::endl;
}

u8 *Memory::GetMemory()
{
    return mmap;
}

void Memory::DMATransfer(int cycles)
{
    /*
     * The DMA transfer takes 162 cycles.
     * Write one byte for each cycle which totals to 160 cycles.
     * TODO: Startup takes 1 cycle and ending takes 1 cycle.
     *
     */

    for(int i = 0; i < cycles; ++i)
    {
        u8 write_value = mmap[dmaAddress + currDMAIndex];
        mmap[MM_OAM_START+currDMAIndex] = write_value;
        ++currDMAIndex;

        if(currDMAIndex == MM_OAM_SIZE)
        {
            dmaActive = false;
            break;
        }
    }
}

void Memory::BootROMRemap()
{
    for(int i=0;i<MM_ROM_BANK_SWITCHABLE_END; ++i)
        mmap[i] = cartridge->GetROM()[i];
}

