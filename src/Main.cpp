#include <iostream>
#include "../include/GameBoy.h"
#include "../include/Debugger.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cout<<"No game specified"<<std::endl;
        exit(1);
    }

    GameBoy gb;

    gb.SetROMPath(argv[1]);
    //gb.Run();
    Debugger debugger(&gb);
    debugger.DebugRun();

    return 0;
}
