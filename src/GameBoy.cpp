#include "../include/GameBoy.h"
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <stdio.h>

GameBoy::GameBoy():
    cpu(&memory),
    memory(&joypad, &cartridge,&timer),
    video(&cpu, &memory),
    joypad(&cpu,&memory),
    timer(&cpu,&memory),
    running(false),
    filepath(),
    frameCycles(0),
    cycleCounter(0)
{}

void GameBoy::Init()
{
    if(!cartridge.LoadRom(filepath))
    {
        std::cerr<<"Error loading game file into cartridge memory" <<std::endl;
        exit(1);
    }

    cartridge.SetMBC();
    cpu.Init();
    memory.Init();
    video.Init();

    std::cout<<"Title: "<<cartridge.GetTitle()<<std::endl;
    std::cout<<"MBC Type: "<<cartridge.GetMBCName()<<std::endl;
}

void GameBoy::Run()
{
    running = true;
    Init();

    cycleCounter = 0;

    float updateTime = 1000.0f/FRAMES_PER_SECOND;
    float startTime = SDL_GetTicks();

    for(;;)
    {
        float currTime = SDL_GetTicks();
        float deltaTime = currTime - startTime;

        joypad.Update();
        if(deltaTime >= updateTime) 
        {
            while(cycleCounter < MAX_CYCLES_PER_FRAME) 
            {
                Step();
            }

            video.DrawFrame();
            startTime = currTime;
            cycleCounter = 0;
        }
    }
}

void GameBoy::SetROMPath(const char *path)
{
    filepath = path;
}

void GameBoy::Step()
{
    unsigned cycles = 0;
    u8 opcode = cpu.Fetch();
    cycles = cpu.Execute(opcode);

    if(memory.DMAActive())
        memory.DMATransfer(cycles);

    cycleCounter+=cycles;

    timer.Tick(cycles);
    video.Tick(cycles);
    cpu.CheckInterrupts();
}
