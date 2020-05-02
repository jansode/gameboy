#ifndef DEBUGGER_COMMANDS
#define DEBUGGER_COMMANDS

bool CommandPrint(std::vector<std::string> &args);
bool CommandBreak(std::vector<std::string> &args);
bool CommandEnable(std::vector<std::string> &args);
bool CommandDisable(std::vector<std::string> &args);
bool CommandRun();
bool CommandContinue();
bool CommandStep();

#endif
