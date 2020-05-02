#include "../include/Cartridge.h"
#include "../include/definitions.h"
#include "../include/memory_map.h"
#include "../include/MBC1.h"

#include <fstream>
#include <iostream>

Cartridge::Cartridge():
    title(CartInfo::CARTRIDGE_TITLE_LENGTH,' '),
    mbcName(),
    romOnly(true),
    hasRAM(false),
    mbcType(0),
    rom(nullptr),
    ramSize(0),
    romSize(0),
    destination(0),
    mbc(nullptr)
{}

Cartridge::~Cartridge()
{
    if(!romOnly) delete(mbc);
    if(hasRAM) delete[] ram;

    delete[] rom;

}

void Cartridge::SetMBC()
{
    switch(mbcType)
    {
        case CartInfo::ROMONLY:
            break;
        case CartInfo::MBC1:
            romOnly = false;
            mbc = new MBC1();
            break;
        default:
            std::cerr<<"Could not determine MBC type for this cartridge."<<std::endl;
            exit(1);
    }
}

bool Cartridge::LoadRom(const char *path)
{
    std::ifstream infile(path, std::ios::in | std::ios::binary);

    if(!infile.is_open()) return false;

    /* Get ROM size */
    infile.seekg(0, std::ios::end);
    unsigned length = infile.tellg();
    infile.seekg(0,std::ios::beg);

    if(length > CartInfo::MAX_CARTRIDGE_ROM_SIZE)
    {
        std::cerr<<"File length exceeds the maximum size of the cartridge memory"<<std::endl;
        return false;
    }

    /* Read header for parsing */
    infile.seekg(0x100,std::ios::cur);

    char headerBuf[0x4F];
    infile.read((char*)&headerBuf[0],0x4F);

    ParseHeader(headerBuf);

    /* Read ROM into cartridge memory */
    infile.seekg(0,std::ios::beg);
    infile.read((char*)&rom[0], length);

    if(!infile)
    {
        std::cerr<<"Error: only "<<infile.gcount() << " could be read"<<std::endl;
        return false;
    }

    infile.close();
    return true;
}

void Cartridge::ParseHeader(const char *header)
{
    /* Read ROM and RAM sizes for cartridge memory */
    romSize = header[0x148-0x100];
    ramSize = header[0x149-0x100];

    switch(romSize)
    {
        case CartInfo::ROM_KB32:
            rom = new u8[32*1024];
            break;
        case CartInfo::ROM_KB64:
            rom = new u8[64*1024];
            break;
        case CartInfo::ROM_KB128:
            rom = new u8[128*1024];
            break;
        case CartInfo::ROM_KB256:
            rom = new u8[256*1024];
            break;
        case CartInfo::ROM_KB512:
            rom = new u8[512*1024];
            break;
        //TODO the rest
        default:
            std::cerr<<"Unimplemented Cartridge ROM allocation for ROM size identifier: 0x"<<std::hex<<(unsigned)romSize<<std::endl;
            exit(1);
    }

    switch(ramSize)
    {
        case CartInfo::RAM_NONE:
            break;
        case CartInfo::RAM_KB2:
            ram = new u8[2*1024];
            hasRAM = true;
            break;
        case CartInfo::RAM_KB8:
            ram = new u8[8*1024];
            hasRAM = true;
            break;
        case CartInfo::RAM_KB32:
            ram = new u8[32*1024];
            hasRAM = true;
            break;
        case CartInfo::RAM_KB128:
            hasRAM = true;
            break;
        case CartInfo::RAM_KB64:
            hasRAM = true;
            break;

        default:
            std::cerr<<"Unimplemented Cartridge RAM allocation for RAM size identifier: 0x"<<std::hex<<(unsigned)romSize<<std::endl;
            exit(1);
    }

    ParseMBC(header);
    ParseTitle(header);
}

void Cartridge::ParseMBC(const char *header)
{
    mbcType = header[0x147-0x100];

    switch(mbcType)
    {
        case CartInfo::ROMONLY:
            mbcName = "None";
            break;
        case CartInfo::MBC1:
            mbcName = "MBC1";
            break;
        case CartInfo::MBC2:
            mbcName = "MBC2";
            break;
        //TODO the rest
    }
}


void Cartridge::ParseTitle(const char *header)
{
    for(u8 i=0;i<CartInfo::CARTRIDGE_TITLE_LENGTH;++i) title[i] = header[0x134-0x100+i];
}

void Cartridge::UpdateMBC(u16 addr, u8 value)
{
    mbc->Update(addr, value);
}

u8 Cartridge::Read(u16 addr)
{
    /* Read from external RAM if enabled. */
    if(mbc->RAMEnabled())
    {
        if(addr >= 0xA000 && addr <=0xBFFF)
        {
            return ram[addr + 8192 /*8KB*/ * mbc->GetCurrentRAMBank()];
        }
    }
    return rom[addr + (MM_ROM_BANK_SWITCHABLE_SIZE * mbc->GetCurrentROMBank())];
}
