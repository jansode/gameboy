#include "../include/Video.h"
#include "../include/CPU.h"
#include "../include/Memory.h"
#include "../include/colors.h"
#include <iostream>

Video::Video(CPU *cpu, Memory *memory):
    cpu(cpu),
    memory(memory),
    scanlineCycles(0),
    frameBuffer(),
    halted(false),
    window(nullptr),
    renderer(nullptr),
    texture(nullptr)
{}

Video::~Video()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Video::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr<<"Couldn't initialize SDL: "<<SDL_GetError()<<std::endl;
        exit(1);
    }
    window = SDL_CreateWindow("Gameboy",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_X*SCREEN_SCALE,
                SCREEN_Y*SCREEN_SCALE,
                SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        std::cerr<<"Error creating window: "<<SDL_GetError()<<std::endl;
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        std::cerr<<"Error creating renderer: "<<SDL_GetError()<<std::endl;
        exit(1);
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, SCREEN_X, SCREEN_Y);

    if(texture == nullptr)
    {
        std::cerr<<"Error creating texture: "<<SDL_GetError()<<std::endl;
        exit(1);
    }
}

void Video::Tick(int cycles)
{
    u8 lcdControl = memory->Read(LCD_CONTROL_REGISTER);
    u8 lcdStatus = memory->Read(LCD_STATUS_REGISTER);
    u8 scanline = memory->GetMemory()[LY_ADDRESS];
    
    /*
     * If lcd display isn't enabled
     * reset some values and return.
     */
    if(false &&(lcdControl & 0x80) == 0)
    {
        /* Dr mario freezes if the following is executed */
        scanlineCycles = 0;
        memory->GetMemory()[LY_ADDRESS] = 0;

        /* When lcd is disabled the lcd mode is set to VBLANK mode. */
        SwitchLCDMode(VBLANK_MODE,lcdStatus);
        return;
    }
    scanlineCycles += cycles;

    UpdateLCDMode(lcdStatus,scanline);

    /* Time for the next scanline. */
    if(scanlineCycles >= CYCLES_PER_SCANLINE)
    {
        scanlineCycles = 0;

        /* Check coincidence flag. */
        if(scanline == memory->Read(LYC_ADDRESS))
        {
            if((lcdStatus & 0x4) && (lcdStatus & 0x40))
                cpu->InterruptRequest(CPU::LCD_INTERRUPT);
        }
        else
            memory->Write(LCD_STATUS_REGISTER, lcdStatus&~0x4);

        if(scanline < VBLANK_START_SCANLINE)
        {
            DrawScanline();
        }
        /* if VBLANK is over */
        else if(scanline > MAX_SCANLINES)
        {
            if((lcdStatus & 0x20))
            {
                cpu->InterruptRequest(CPU::LCD_INTERRUPT);
            }
            SwitchLCDMode(OAM_READING_MODE,lcdStatus);
            memory->GetMemory()[LY_ADDRESS] = 0;
            return;
        }

        /*
        * Increment the scanline counter
        * can't use Write here because it would reset the counter.
        */
        memory->GetMemory()[LY_ADDRESS] = ++scanline;
    }
}

void Video::UpdateLCDMode(u8 lcdStatus, u8 scanline)
{
    u8 mode = lcdStatus & 3;
    u8 newMode = mode;

    switch(mode)
    {
        /*
         * The LCD controller
         * is in the VBLANK period.
         */
        case VBLANK_MODE:
            break;
        /*
         * The LCD controller
         * is reading from OAM memory.
         */
        case OAM_READING_MODE:
        {
            if(scanlineCycles >= LCD_MODE2_END)
            {
                newMode = OAM_VRAM_READING_MODE;
            }
            break;
        }
        /*
         * The LCD controller 
         * is reading from both OAM and VRAM.
         */
        case OAM_VRAM_READING_MODE:
        {
            if(scanlineCycles >= LCD_MODE3_END)
            {
                newMode = HBLANK_MODE; 
                if((lcdStatus & 0x8))
                    cpu->InterruptRequest(CPU::LCD_INTERRUPT);
            }
            break;
        }
        /* The LCD controller is in the HBLANK period. */
        case HBLANK_MODE:
        {
            if(scanline == VBLANK_START_SCANLINE)
            {
                /* This doesn't work? Shouldn't it be enabled first? */
                //if(lcdStatus & 0x10)
                    cpu->InterruptRequest(CPU::VBLANK_INTERRUPT);

                newMode = VBLANK_MODE;
                break;
            }

            if(scanlineCycles >= LCD_MODE0_END)
            {
                newMode = OAM_READING_MODE;
                if((lcdStatus & 0x20))
                    cpu->InterruptRequest(CPU::LCD_INTERRUPT);
            }
            break;
        }
        default:
        {
            std::cerr<<"Unknown LCD mode: "<<std::hex<<(unsigned)mode<<std::endl;
            exit(1);
        }
    }

    if(mode != newMode)
    {
        /* Write new mode into lcdstatus register. */
        SwitchLCDMode(newMode,lcdStatus);
    }
}

void Video::DrawScanline()
{
    u8 lcdControl = memory->Read(LCD_CONTROL_REGISTER);
    
    /* Draw background if enabled. */
    if((lcdControl & 1)) DrawBackground(); 
    //else DrawBlank();

    /* Draw sprites if enabled. */
    if((lcdControl & 2)) DrawSprites(); 
}

void Video::DrawBlank()
{
    for(u8 i=0; i<SCREEN_X;++i)
    {
        /*TODO don't hardcode the values*/
        u8 positionY = memory->GetMemory()[LY_ADDRESS];
        frameBuffer[positionY][i][0] = 0x9b;
        frameBuffer[positionY][i][1] = 0xbc;
        frameBuffer[positionY][i][2] = 0x0f;
    }
}

void Video::DrawBackground()
{
    u8 scrollY = memory->Read(SCY_ADDRESS);    
    u8 scrollX = memory->Read(SCX_ADDRESS);    
    u8 windowY = memory->Read(WY_ADDRESS);

    /* This needs to subtract 7 */
    u8 windowX = memory->Read(WX_ADDRESS)-7;

    u8 lcdControl = memory->Read(LCD_CONTROL_REGISTER);

    /*
     * Tile data address range 
     * 0: 0x8800-0x97FF (signed numbering)
     * 1: 0x8000-0x8FFF (unsigned numbering)
     */
    u16 tileDataStart = (lcdControl & 0x10) ?
        0x8000 : 0x8800;

    //Window tile map display select
    u16 windowMapStart = (lcdControl & 0x40)?
        0x9C00 : 0x9800;

    /* Background tile map display select */
    u16 backgroundMapStart = (lcdControl & 0x8)?
        0x9C00 : 0x9800;


    bool windowEnabled = false;

    /*
     * Enable window if WY and WX are in the correct range 
     * and window is enabled in LCD Control register.
     */
    if((lcdControl & 0x20) && windowX <= 166 && windowY <= 143)
       windowEnabled = true; 

    /* Current y position */
    u8 positionY = memory->GetMemory()[LY_ADDRESS];
    
    /* Current y position to draw */
    u8 viewY = (windowEnabled)?positionY+scrollY-windowY:positionY+scrollY;

    /* Vertical tile coordinate */
    u8 tilesY = (viewY / 8) % 32;

    /* Vertical offset into the tile */
    u8 tileYOffs = viewY % 8;

    /* Draw the scanline */
    for(u8 i=0; i<SCREEN_X; ++i)
    {
        /* Horizontal tile coordinate */
        u8 tilesX = ((scrollX+i) / 8) % 32;

        /* Horizontal offset into the tile */
        u8 tileXOffs = (scrollX+i) % 8;

        u16 tileMapStart = (windowEnabled)?windowMapStart:backgroundMapStart;
        u8 tileNumber = memory->Read(tileMapStart+(tilesX+(32*tilesY)));
        u8 byte1, byte2;

        /* Unsigned tile numbers */
        if(tileDataStart == 0x8000)
        {
            u16 tileAddr = tileDataStart + tileNumber*TILE_SIZE;
            byte1 = memory->Read(tileAddr+(tileYOffs*2));
            byte2 = memory->Read((tileAddr+(tileYOffs*2))+1);
        }
        /* Signed tile numbers */
        else
        {
            u16 tileAddr = tileDataStart + ((s8)tileNumber+128)*TILE_SIZE;
            byte1 = memory->Read(tileAddr+tileYOffs*2);
            byte2 = memory->Read((tileAddr+tileYOffs*2)+1);
        }

        u8 upperbit = (((0x80 >> tileXOffs) & byte1) > 0)?1:0;
        u8 lowerbit = (((0x80 >> tileXOffs) & byte2) > 0)?1:0;
        u8 colorID = ((upperbit << 1) | lowerbit); 

        u32 shade = GetShade(colorID,BGP_REGISTER);

        frameBuffer[positionY][i][0] = (shade & 0xFF0000) >> 16;
        frameBuffer[positionY][i][1] = (shade & 0xFF00) >> 8;
        frameBuffer[positionY][i][2] = (shade & 0xFF);
    }
}

void Video::DrawSprites()
{
    //u8 lcdControl = memory->Read(LCD_CONTROL_REGISTER);

    /* Get the sprite Y size */
    //u8 spriteSizeY = (lcdControl & 0x2)?16:8;     

    /* Loop through each OAM entry */
    for(int i=0; i<MM_OAM_SIZE; i+=OAM_ENTRY_SIZE)
    {
        u8 spriteY = memory->Read(MM_OAM_START+i)-16; 
        u8 spriteX = memory->Read(MM_OAM_START+i+1)-8; 
        u8 tileNumber = memory->Read(MM_OAM_START+i+2);
        u8 attributes = memory->Read(MM_OAM_START+i+3);

        u8 currScanline = memory->Read(LY_ADDRESS);

        /* Do we need to draw the sprite on this scanline? */
        if(((spriteY+8) <= currScanline) || (spriteY > currScanline)) continue;

        /* Offscreen values hide the sprite. */
        if(spriteX == 0 || spriteX >=168 || spriteY+8 == 0 || spriteY >= 160) continue; 

        bool yFlip = (attributes & 0x40)?true:false;
        bool xFlip = (attributes & 0x20)?true:false;

        u8 spriteYOffs = currScanline - spriteY;
        u16 tileAddr = MM_TILE_DATA_START +(tileNumber*TILE_SIZE);
        u8 byte1, byte2;

        if(yFlip)
        {
            byte1 = memory->Read(tileAddr+TILE_SIZE-(spriteYOffs*2));
            byte2 = memory->Read(tileAddr+TILE_SIZE-(spriteYOffs*2)+1);
        }
        else
        {
            byte1 = memory->Read(tileAddr+(spriteYOffs*2));
            byte2 = memory->Read(tileAddr+(spriteYOffs*2)+1);
        }

        for(int j=0; j<8; ++j)
        {
            u8 upperbit = (((0x80 >> j) & byte1) > 0)?1:0;
            u8 lowerbit = (((0x80 >> j) & byte2) > 0)?1:0;
            u8 colorID = ((upperbit << 1) | lowerbit); 

            /* ColorID 0 is transparent for sprites so we won't draw it */
            if(colorID == 0) continue;

            u16 palletteAddr = ((attributes & 0x10) > 0)?OBP1_REGISTER:OBP0_REGISTER;
            u32 shade = GetShade(colorID,palletteAddr);

            if(xFlip)
            {
                frameBuffer[currScanline][spriteX+7-j][0] = (shade & 0xFF0000) >> 16;
                frameBuffer[currScanline][spriteX+7-j][1] = (shade & 0xFF00) >> 8;
                frameBuffer[currScanline][spriteX+7-j][2] = (shade & 0xFF);
            }
            else
            {
                frameBuffer[currScanline][spriteX+j][0] = (shade & 0xFF0000) >> 16;
                frameBuffer[currScanline][spriteX+j][1] = (shade & 0xFF00) >> 8;
                frameBuffer[currScanline][spriteX+j][2] = (shade & 0xFF);
            }
        }
    }
}

void Video::DrawFrame()
{
    SDL_UpdateTexture(texture, NULL, frameBuffer, SCREEN_X*3); 
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

u32 Video::GetShade(u8 colorID, u16 palletteAddress)
{
    u8 pallette = memory->Read(palletteAddress);

    /* Here we multiply by 2 because the colorIDs in the pallette are 2 bits each .*/
    unsigned colorNum = colorID*2;

    switch((pallette & (0x3<<colorNum))>>colorNum)
    {

        case WHITE:
            return COLOR_WHITE;
        case LIGHT_GRAY:
            return COLOR_LIGHT_GRAY;
        case DARK_GRAY:
            return COLOR_DARK_GRAY;
        case BLACK:
            return COLOR_BLACK;
        default:
        {
            std::cerr<<"No shade could be determined for this colorID"<<std::endl;
            exit(1);
        }
    }
}

void Video::SwitchLCDMode(u8 newMode, u8 lcdStatusValue)
{
    memory->Write(LCD_STATUS_REGISTER, (lcdStatusValue & 0xFC) | newMode);
}
