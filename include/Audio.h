#ifndef AUDIO_H
#define AUDIO_H

#include "Memory.h"

#include <SDL2/SDL.h>

class Audio
{
    public:
        Audio(Memory *memory);
        ~Audio();
        void Init();
        void Tick(int cycles);

    private:
        unsigned frameSequencerCycles;

        u16 GetChannel1Frequency();

        SDL_AudioDeviceID device;
        Memory *memory;


};

#endif
