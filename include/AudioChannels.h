#ifndef AUDIO_CHANNELS_H
#define AUDIO_CHANNELS_H

#include "Memory.h"

class AudioChannels
{
    public:
        AudioChannels(Memory *memory);
        u16 GetChannel1Frequency();

    private:
        Memory *memory;
};

#endif
