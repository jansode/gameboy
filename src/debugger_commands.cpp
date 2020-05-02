#include "../include/Debugger.h"
#include <iostream>
#include <sstream>
#include "../include/util.h"

bool Debugger::CommandRun()
{
    if(gameboy->running)
    {
        std::cout<<"Emulation already running"<<std::endl;
        return false;
    }

    running = true;
    return true;
}

bool Debugger::CommandContinue()
{
    if(!running)
    {
        std::cout<<"Emulation not running."<<std::endl;
        return false;
    }
    breaked = false;
    return true;
}

bool Debugger::CommandPrint(std::vector<std::string> &args)
{
    if(args.size() < 3)
    {
        std::cout<<"Too few arguments"<<std::endl;
        return false;
    }

    u16 address = ParseHexValue(args[1]);

    unsigned amount = stoi(args[2]);

    gameboy->memory.MemoryDump(address,address+amount);
    return true;
}

bool Debugger::CommandBreak(std::vector<std::string> &args)
{
    if(args.size() == 0) return false;
    else if(args[0] == "pc")
    {
        if(args.size() < 2) return false;

        u16 value = ParseHexValue(args[1]);
        AddBreakCondition([=](){return (gameboy->cpu.GetCurrentAddress() == value);});
        std::cout<<"Breakpoint added when PC value is 0x"<<std::hex<<value<<std::endl;
        return true;
    }
    else if(args[0] == "i")
    {
        u16 value = ParseHexValue(args[1]);
        AddBreakCondition([=](){return (gameboy->cpu.GetNextInstruction() == value);});
        std::cout<<"Breakpoint added when next instruction value is 0x"<<std::hex<<value<<std::endl;
        return true;
        
    }
    else if(args.size() == 3)
    {
        u16 address = ParseHexValue(args[0]);
        u16 value = ParseHexValue(args[1]);

        AddBreakCondition([=](){return (gameboy->memory.GetMemory()[address] == value);});
        std::cout<<"Breakpoint added when memory location 0x"<<std::hex<<(unsigned) address<<" has value 0x"<<std::hex<<(unsigned)value<<std::endl;
        return true;
    }
    else
    {
        u16 address = ParseHexValue(args[0]);
        AddBreakpoint(address);
        std::cout<<"Breakpoint added at address 0x" << std::hex << address <<std::endl;
        return true;
    }
}

bool Debugger::CommandEnable(std::vector<std::string> &args)
{
    if(args.size() == 0) return false;

    if(args[0] == "registers" || args[0] == "r")
    {
        showRegs = true;
    }
    else if(args[0] == "instructions" || args[0] == "i")
    {
        showInstr = true;
    }
    else if(args[0] == "next" || args[0] == "n")
    {
        showNext = true;
    }
    return true;
}

bool Debugger::CommandDisable(std::vector<std::string> &args)
{
    if(args.size() == 0) return false;

    if(args[0] == "registers" || args[0] == "r")
    {
        showRegs = false;
    }
    else if(args[0] == "instructions" || args[0] == "i")
    {
        showInstr = false;
    }
    else if(args[0] == "next" || args[0] == "n")
    {
        showNext = false;
    }
    return true;
}

bool Debugger::CommandStep()
{
    if(!running)
    {
        std::cout<<"Cannot step, emulation not running." << std::endl;
        return false;
    }

    gameboy->Step();
    std::cout << "Stepping" << std::endl;
    if(showInstr)
    {
        std::cout<<"Next instruction: "<<std::hex<<(unsigned)gameboy->memory.Read(gameboy->cpu.GetCurrentAddress())<<std::endl;
    }
    if(showRegs)
    {
        gameboy->cpu.PrintRegisters();
    }
    if(showNext)
    {
        u16 addr = gameboy->cpu.GetCurrentAddress(); 
        gameboy->memory.MemoryDump(addr,addr+100);
    }
    return true;
}
