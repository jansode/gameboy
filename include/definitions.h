#ifndef DEFINITIONS_H
#define DEFINITIONS_H

const unsigned int CPU_CLOCK_SPEED = 4194304;
const float FRAMES_PER_SECOND = 59.7;

const unsigned int MAX_CYCLES_PER_FRAME = 69905;

const unsigned int SCREEN_X = 160;
const unsigned int SCREEN_Y = 144;
const unsigned int SCREEN_SCALE = 6;

const unsigned int CYCLES_PER_SCANLINE = 456;
const unsigned int VBLANK_START_SCANLINE = 144;
const unsigned int MAX_SCANLINES = 153;

const unsigned int LCD_MODE2_END = 80;
const unsigned int LCD_MODE3_END = 172;
const unsigned int LCD_MODE0_END = 284;
const unsigned int VBLANK_DURATION = 4560;

const unsigned int TILE_SIZE = 0x10;

const unsigned int OAM_ENTRY_SIZE = 0x4;

#endif
