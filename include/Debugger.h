#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>

#include "definitions.h"
#include "GameBoy.h"

struct Command
{
    std::string name;
    std::vector<std::string> args;
};

class GameBoy;

class Debugger
{
    public: 
        Debugger(GameBoy *gameboy); 
        void Init();
        void DebugRun();
        void AddBreakpoint(u16 address);
        void AddBreakCondition(std::function<bool()> condition);
        void PrintBreakpoints();

        void GetCommands();
        void BreakConditionCheck();

        #include "debugger_commands.h"

        void SetShowNextRegister(bool value){showNext=value;}
        void SetShowRegisters(bool value){showRegs=value;}
        void SetShowInstructions(bool value){showInstr=value;}
        inline bool ShowNextInstruction(){return showNext;}
        inline bool ShowRegisters(){return showRegs;}
        inline bool ShowInstructions(){return showInstr;}
        inline void ClearBreakpoints(){breakpoints.clear();}
        inline void Quit(){quit = true;}
        bool IsBreakpoint(u16 address);

        Command PromptCommand();

        inline GameBoy *GetGameBoy(){return gameboy;}

    private:
        GameBoy*    gameboy;
        bool        running;
        bool        breaked;
        bool        debug;
        bool        showRegs;
        bool        showInstr;
        bool        showNext;
        bool        quit;

        Command                                     prevCommand;
        std::unordered_set<u16>                     breakpoints;
        std::vector<std::function<bool()>>          breakConditions;
};

#endif
