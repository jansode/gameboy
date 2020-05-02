#ifndef JOYPAD_H
#define JOYPAD_H

#include "definitions.h"
#include "types.h"
#include <SDL2/SDL.h>
#include <unordered_map>

class CPU;
class Memory;

class Joypad
{
    public:
        enum KeysType 
        {
            BUTTON_KEYS         =0x20,
            DIRECTIONAL_KEYS    =0x10
        };
        enum Button
        {
            BUTTON_A        =0x1,
            BUTTON_B        =0x2,
            BUTTON_SELECT   =0x4,
            BUTTON_START    =0x8
        };
        enum Direction 
        {
            DIRECTION_RIGHT =0x10,
            DIRECTION_LEFT  =0x20,
            DIRECTION_UP    =0x40,
            DIRECTION_DOWN  =0x80
        };

        Joypad(CPU *cpu, Memory *memory);
        void Update();
        void SetKey(u8 key);
        void UnsetKey(u8 key);

        u8 GetState();

    private:
        const std::unordered_map<int, u8> keys
        {
            {SDLK_UP,   DIRECTION_UP},
            {SDLK_DOWN, DIRECTION_DOWN},
            {SDLK_LEFT, DIRECTION_LEFT}, 
            {SDLK_RIGHT,DIRECTION_RIGHT},
            {SDLK_q,    BUTTON_A}, 
            {SDLK_w,    BUTTON_B},
            {SDLK_a,    BUTTON_START}, 
            {SDLK_s,    BUTTON_SELECT}
        };

        CPU*        cpu;
        Memory*     memory;
        u8          state;
};

#endif
