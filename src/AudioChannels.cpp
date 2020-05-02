#include "../include/AudioChannels.h"

AudioChannels::AudioChannels(Memory *memory):
    memory(memory)
{}

#define MEM(x) memory->GetMemory()[x]

u16 AudioChannels::GetChannel1Frequency()
{
    return (((u16)MEM(NR14_REGISTER)&7)<<8) | MEM(NR13_REGISTER);
}
