#include "../include/Audio.h"
#include "../include/types.h"
#include "../include/definitions.h"

#include <iostream>

const unsigned sampleRate = 44100;


Audio::Audio(Memory *memory):
    frameSequencerCycles(0),
    memory(memory)
{}

Audio::~Audio()
{
    SDL_CloseAudioDevice(device);
}

void Audio::Init()
{
    /* Initialize SDL audio */
    if(SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr<<"Could not initialize SDL audio"<<std::endl;
        exit(1);
    }

    SDL_AudioSpec desired, obtained;
    SDL_memset(&desired, 0, sizeof(desired));

    desired.freq = sampleRate;
    desired.format = AUDIO_S16SYS;
    desired.channels = 2;
    desired.samples = 4096;
    desired.callback = [](void*, Uint8 *stream, int len)
    {
        /*
        s16 *stream16 = (s16*)stream;

        unsigned bytesPerPeriod1 = sampleRate / channels.GetChannel1Frequency(); 

        for(int i=0; i<len; ++i)
        {
            s16 outputValue = bytesPerPeriod1*i;
            stream16[i] = outputValue;
        }
        */
    };

    device = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if(device == 0)
    {
        std::cerr<<"Could not open audio: "<<SDL_GetError()<<std::endl;
        exit(1);
    }

    SDL_PauseAudio(0);
}

void Audio::Tick(int cycles)
{

}

u16 Audio::GetChannel1Frequency()
{
    //return (((u16)MEM(NR14_REGISTER)&7)<<8) | MEM(NR13_REGISTER);
    return 0;

}



