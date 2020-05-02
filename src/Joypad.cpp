#include "../include/Joypad.h"
#include "../include/Memory.h"
#include "../include/CPU.h"
#include <iostream>

Joypad::Joypad(CPU *cpu, Memory *memory):
    cpu(cpu),
    memory(memory),
    state(0x00)
{}

void Joypad::Update()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_KEYDOWN:
            {
                if(e.key.keysym.sym == SDLK_z) exit(1);
                auto key = keys.find(e.key.keysym.sym);
                if(key != keys.end()) 
                    SetKey(key->second);
                break;
            }
            case SDL_KEYUP:
            {
                auto key = keys.find(e.key.keysym.sym);
                if(key != keys.end()) 
                    UnsetKey(key->second);
                break;
            }
            default:
                break;
        }
    }
}

u8 Joypad::GetState()
{
    /*
     * Select bit 4 or 5 for either Button keys
     * or directional keys. 
     *
     * If the bit 4 is set, bits 0-3 are interpreted
     * as directional keys.
     *
     * If the bit 5 is set, bits 0-3 are interpreted
     * as button keys.
     *
     * The bits in this register are inverted so 0
     * means set and 1 means unset.
     */

    u8 joypadReg = ~memory->GetMemory()[JOYPAD_REGISTER];

    u8 keystype = (joypadReg & BUTTON_KEYS)?BUTTON_KEYS:DIRECTIONAL_KEYS;
    
    u8 returnval = (keystype==BUTTON_KEYS)?
        ~(((state & 0xF)|BUTTON_KEYS)&0x3F):
        ~((((state & 0xF0)>>4)|DIRECTIONAL_KEYS)&0x3F);

    return returnval;
}

void Joypad::SetKey(u8 key)
{
    /*
     * If key was previously unset and if 
     * interrupt requested for this keytype, 
     * request a joypad interrupt
     */
    if((state & key)==0)
    {
        u8 joypadReg = ~memory->GetMemory()[JOYPAD_REGISTER];

        if((key & 0xF0) && (joypadReg & DIRECTIONAL_KEYS))
            cpu->InterruptRequest(CPU::JOYPAD_INTERRUPT);
        if((key & 0xF) && (joypadReg & BUTTON_KEYS))
            cpu->InterruptRequest(CPU::JOYPAD_INTERRUPT);
    }
    state = key;
}

void Joypad::UnsetKey(u8 key)
{
    state &= ~key;
}

