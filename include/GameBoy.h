#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "CPU.h"
#include "Memory.h"
#include "Cartridge.h"
#include "Joypad.h"
#include "Video.h"
#include "Timer.h"
#include "definitions.h"
#include "types.h"
#include "Debugger.h"

#include <string>
#include <unordered_set>
#include <vector>

class GameBoy
{
    friend class Debugger;

    public:
        GameBoy();
        void Init();

        /*
         * Set path to ROM file 
         *
         */
        void SetROMPath(const char *path);

        /*
         * Start emulation
         *
         */
        void Run();

        /*
         * Single step of the processor
         *
         */
        void Step();

    private:
        CPU         cpu;
        Memory      memory; 
        Video       video;
        Cartridge   cartridge;
        Joypad      joypad;
        Timer       timer;

        bool        running;

        const char* filepath;
        unsigned    frameCycles;
        unsigned    cycleCounter;
};

#endif
