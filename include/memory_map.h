#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include "types.h"

const u16 MM_ROM_BANK00_START = 0x0;
const u16 MM_ROM_BANK00_END = 0x3FFF;
const u16 MM_ROM_BANK00_SIZE = 0x4000;

const u16 MM_ROM_BANK_SWITCHABLE_START = 0x4000;
const u16 MM_ROM_BANK_SWITCHABLE_END = 0x7FFF;
const u16 MM_ROM_BANK_SWITCHABLE_SIZE = 0x4000;

const u16 MM_VRAM_START = 0x8000;
const u16 MM_VRAM_END = 0x9FFF;
const u16 MM_VRAM_SIZE = 0x2000;

const u16 MM_TILE_DATA_START = MM_VRAM_START;
const u16 MM_TILE_DATA_END = 0x97FF;
const u16 MM_TILE_DATA_SIZE = 0x17FF;

const u16 MM_OAM_START = 0xFE00;
const u16 MM_OAM_END = 0xFE9F;
const u16 MM_OAM_SIZE = 0xA0;


/*
 * Timer registers
 */
const u16 DIV_REGISTER = 0xFF04;
const u16 TIMA_REGISTER = 0xFF05;
const u16 TMA_REGISTER = 0xFF06;
const u16 TAC_REGISTER  = 0xFF07;

/*
 * Interrupt registers
 *
 */

const u16 INTERRUPT_ENABLED_REGISTER = 0xFFFF;
const u16 INTERRUPT_REQUEST_REGISTER = 0xFF0F;

/*
 * Interrupt service routine locations
 *
 */
const u16 VBLANK_SERVICE_ROUTINE = 0x40;
const u16 LCD_SERVICE_ROUTINE = 0x48;
const u16 TIMER_SERVICE_ROUTINE = 0x50;
const u16 SERIAL_SERVICE_ROUTINE = 0x58;
const u16 JOYPAD_SERVICE_ROUTINE = 0x60;


/*
 * Writing 1 to this register unmaps the boot rom 
 *
 */
const u16 DISABLE_BOOT_ROM_REGISTER = 0xFF50;


/*
 * Joypad register
 *
 */
const u16 JOYPAD_REGISTER = 0xFF00;


/*
 * LCD registers
 *
 */
const u16 LCD_CONTROL_REGISTER = 0xFF40;
const u16 LCD_STATUS_REGISTER = 0xFF41;

/*
 * Scroll position of the
 * viewing area
 *
 */
const u16 SCY_ADDRESS = 0xFF42;
const u16 SCX_ADDRESS = 0xFF43;


/*
 * LCDC y-coordinate 
 * Holds the value of the vertical line to which 
 * present data is being transferred to the LCD Driver.
 *
 */
const u16 LY_ADDRESS = 0xFF44;


/*
 * LY compare register
 *
 */
const u16 LYC_ADDRESS = 0xFF45;


/*
 * Upper left position of the 
 * window area.
 *
 */
const u16 WY_ADDRESS = 0xFF4A;
const u16 WX_ADDRESS = 0xFF4B;


/*
 * Writing to this address launches a DMA transfer
 * from ROM or RAM to OAM memory.
 */
const u16 DMA_TRANSFER_ADDRESS = 0xFF46;


 /* Pallette registers */
const u16 BGP_REGISTER = 0xFF47;
const u16 OBP0_REGISTER = 0xFF48;
const u16 OBP1_REGISTER = 0xFF49;

/* Sound registers */

const u16 NR50_REGISTER = 0xFF24; /* Channel control/ON-OFF/Volume */
const u16 NR51_REGISTER = 0xFF25; /* Selection of sound output terminal */
const u16 NR52_REGISTER = 0xFF26; /* Sound on/off */

const u16 NR10_REGISTER = 0xFF10; /* Channel1 sweep register */
const u16 NR11_REGISTER = 0xFF11; /* Channel1 sound length/wave pattern duty */
const u16 NR12_REGISTER = 0xFF12; /* Channel1 volume envelope */
const u16 NR13_REGISTER = 0xFF13; /* Channel1 frequency lo */
const u16 NR14_REGISTER = 0xFF14; /* Channel1 frequency hi */

const u16 NR21_REGISTER = 0xFF21; /* Channel2 sound length/wave pattern duty */
const u16 NR22_REGISTER = 0xFF17; /* Channel2 volume envelope */
const u16 NR23_REGISTER = 0xFF18; /* Channel2 frequency lo data */
const u16 NR24_REGISTER = 0xFF19; /* Channel2 frequency hi data */

const u16 NR30_REGISTER = 0xFF1A; /* Channel3 sound on/off */
const u16 NR31_REGISTER = 0xFF1B; /* Channel3 sound length */
const u16 NR32_REGISTER = 0xFF1C; /* Channel3 select output level */
const u16 NR33_REGISTER = 0xFF1D; /* Channel3 frequency's lower data */
const u16 NR34_REGISTER = 0xFF1E; /* Channel3 frequency's higher data */

/*
 * Waveform storage for arbitrary sound data.
 * 32 4-bit samples that are played back 
 * upper 4 bits first.
 */
const u16 WAVE_PATTERN_RAM_START = 0xFF30; 
const u16 WAVE_PATTERN_RAM_END = 0xFF3F;


const u16 NR41_REGISTER = 0xFF20; /* Channel4 sound length */ 
const u16 NR42_REGISTER = 0xFF21; /* Channel4 volume envelope */
const u16 NR43_REGISTER = 0xFF22; /* Channel4 polynomial counter */
const u16 NR44_REGISTER = 0xFF23; /* Channel4 counter/consecutive, initial */

#endif
