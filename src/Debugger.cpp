#include "../include/Debugger.h"
#include <iostream>
#include <unordered_set>
#include <sstream>
#include <SDL2/SDL.h>

Debugger::Debugger(GameBoy *gameboy):
    gameboy(gameboy),
    running(false),
    breaked(false),
    debug(false),
    showRegs(false),
    showInstr(false),
    showNext(false),
    quit(false)
{}

void Debugger::DebugRun()
{
    while(!running)
    {
        GetCommands();
        if(quit) return;
    }

    gameboy->Init();
    gameboy->cycleCounter = 0;

    float updateTime = 1000.0f/FRAMES_PER_SECOND; 
    float startTime = SDL_GetTicks();
    for(;;)
    {
        float currTime = SDL_GetTicks();
        float deltaTime = currTime - startTime;

        gameboy->joypad.Update();
        if(deltaTime >= updateTime)
        {
            while(gameboy->cycleCounter < MAX_CYCLES_PER_FRAME)
            {
                if(breaked)
                {
                    std::cout<<"Execution stopped at breakpoint 0x"<<std::hex<<(unsigned)gameboy->cpu.GetCurrentAddress()<<std::endl;
                    GetCommands();
                }
                else
                {
                    if(showInstr) 
                    {
                        std::cout<<"Next instruction: "<<std::hex<<(unsigned)gameboy->memory.Read(gameboy->cpu.GetCurrentAddress())<<std::endl;
                    }
                    if(showRegs) gameboy->cpu.PrintRegisters();
                    if(showNext)
                    {
                        u16 addr = gameboy->cpu.GetCurrentAddress();
                        gameboy->memory.MemoryDump(addr,addr+100);
                    }
                    gameboy->Step();
                }

                if(IsBreakpoint(gameboy->cpu.GetCurrentAddress()))
                {
                    breaked = true;
                }

                BreakConditionCheck();
            }

            gameboy->video.DrawFrame();
            startTime = currTime;
            gameboy->cycleCounter = 0;
        }
    }
}

Command Debugger::PromptCommand()
{
    std::string input; 
    std::cout<<"[Debug]>";
    std::getline(std::cin, input);

    std::vector<std::string> words;
    if(std::cin.fail())
        exit(1);

    Command command;

    /* Give prev command if input is empty or only spaces */
    if(input.empty() || input.find_first_not_of(' ') == std::string::npos)
    {
        command.name = "prev";
        return command;
    }


    std::stringstream ss(input); 
    std::string buf;
    for(int i=0; ss >> buf; ++i)
    {
        if(i==0) 
            command.name = buf;
        else
            command.args.push_back(buf);
    }

    return command; 
}

void Debugger::AddBreakpoint(u16 address)
{
    breakpoints.insert(address);
}

void Debugger::AddBreakCondition(std::function<bool()> condition)
{
    breakConditions.push_back(condition);
}

bool Debugger::IsBreakpoint(u16 address)
{
    auto found = breakpoints.find(address);
    if(found == breakpoints.end()) 
        return false;

    return true;
}

void Debugger::BreakConditionCheck()
{
    for(auto condition : breakConditions)
    {
        if(condition())
            breaked = true;
    }
}

void Debugger::PrintBreakpoints()
{
    std::cout<<"Breakpoints:"<<std::endl;
    if(breakpoints.empty())
        std::cout<<"No breakpoints set"<<std::endl;
    for(auto bp : breakpoints)
    {
        std::cout<<"0x"<<std::hex<<bp<<std::endl;
    }
}

void Debugger::GetCommands()
{
    bool command_done = false;
    while(!command_done)
    {
        Command command = PromptCommand();

        if(command.name == "prev")
            command = prevCommand;

        if(command.name == "run" || command.name == "r")
        {
            if(CommandRun()) command_done = true;
            else continue;
        }
        else if(command.name == "continue" || command.name == "c")
        {
            if(CommandContinue()) command_done = true;
            else continue;
        }
        else if(command.name == "quit" || command.name == "q")
        {
            quit = true;
            command_done = true;
        }
        else if(command.name == "break" || command.name == "b")
        {
            if(CommandBreak(command.args)) command_done = true;
            else continue;
        }
        else if(command.name == "clear")
        {
            std::cout<<"Clearing breakpoints"<<std::endl;
            ClearBreakpoints(); 
        }
        else if(command.name == "print" || command.name == "p")
        {
            if(!CommandPrint(command.args)) continue;
        }
        else if(command.name == "step" || command.name == "s") 
        {
            CommandStep();
        }
        else if(command.name == "enable" || command.name == "e")
        {
            if(!CommandEnable(command.args)) continue;
        }
        else if(command.name == "disable" || command.name == "d")
        {
            if(!CommandDisable(command.args)) continue;
        }
        else
        {
            std::cout<<"Unknown command"<<std::endl;
            continue;
        }

       prevCommand = command;
    }
}


