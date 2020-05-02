#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

#include "MBC.h"
#include "definitions.h"
#include "types.h"
#include "cartinfo.h"

class Cartridge
{
    public:
        Cartridge();
        ~Cartridge();

        /*
         * Loads ROM binary into cartridge memory.
         */
        bool LoadRom(const char *path);


        /*
         * Parses cartridge header info.
         */
        void ParseHeader(const char *header);
        /*
         * Reads the byte at location 0x147
         * to determine the type of MBC 
         */
        void ParseMBC(const char *header);

        /* Reads the cartridge title
         * in upper case ASCII starting
         * from location 0x134.
         */
        void ParseTitle(const char *header);

        void SetMBC();

        void UpdateMBC(u16 addr, u8 value);

        u8 Read(u16 addr);

        u8 GetROMRAMMode();
        inline u8 *GetROM(){return rom;}
        inline u8 *GetRAM(){return ram;}
        inline u8 GetMBCType(){return mbcType;}
        inline std::string GetTitle(){return title;}
        inline std::string GetMBCName(){return mbcName;}
        inline bool HasMBC(){return !romOnly;}
    private:
        std::string title;
        std::string mbcName;

        bool        romOnly;
        bool        hasRAM;

        u8          mbcType;
        u8*         rom;
        u8*         ram;
        u8          ramSize;
        u8          romSize;
        u8          destination; 

        MBC*        mbc;
};

#endif
