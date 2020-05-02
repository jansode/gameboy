#ifndef VIDEO_H
#define VIDEO_H

#include "definitions.h"
#include "types.h"
#include <SDL2/SDL.h>

class CPU;
class Memory;

class Video
{
    public:
        enum LCDMode
        {
            HBLANK_MODE,
            VBLANK_MODE,
            OAM_READING_MODE,
            OAM_VRAM_READING_MODE            
        };

        enum Colors
        {
            WHITE,
            LIGHT_GRAY,
            DARK_GRAY,
            BLACK
        };

        Video(CPU *cpu, Memory *memory);
        ~Video();
        void Init();
        void Tick(int cycles);

        /* Draws the current scanline */
        void DrawScanline();

        /* Draws the background and window */
        void DrawBackground();

        /* Draws the sprites */
        void DrawSprites();

        /* Draws a blank scanline */
        void DrawBlank();
        
        /* Renders a frame on the screen */
        void DrawFrame();

        /* Updates the LCD Mode */
        void UpdateLCDMode(u8 lcdStatus, u8 scanline);

        /* Writes the new LCD mode value to the LCD status register */ 
        void SwitchLCDMode(u8 newMode, u8 lcdStatusValue);

        /*
         * Returns the RGB value associated 
         * with the colorID of a given pallette.
         */
        u32 GetShade(u8 colorID, u16 palletteAddress);

        inline bool IsHalted(){return halted;}
    private: 
        CPU *cpu;
        Memory *memory;
        unsigned scanlineCycles;
        u8 frameBuffer[SCREEN_Y][SCREEN_X][3];

        bool halted; 

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
};

#endif
