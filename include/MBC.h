#ifndef MBC_H
#define MBC_H

#include "types.h"

class MBC
{
    public:
        MBC();
        virtual ~MBC();
        virtual void Update(u16 addr, u8 value) = 0;

        inline u8 GetCurrentROMBank(){return currentROMBank;}
        inline u8 GetCurrentRAMBank(){return currentRAMBank;}
        inline bool RAMEnabled(){return ramEnabled;}

    protected:
        u8      currentROMBank;
        u8      currentRAMBank;
        bool    ramEnabled;
};

#endif
