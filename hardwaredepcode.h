/*
created by Aldo Buson

this code is hardware dependent. you should change it according to the target display
this implementation is only for development purpose and draw text in Windows console.
it is based on a 80*24 buffer. vt100 code write only in this buffer.
to display the buffer the hw_refreshVideo function have to be called.
in a real implementation every single command should write directly to the display
memory.
*/

#ifndef HARDWAREDEPCODE_H_INCLUDED
#define HARDWAREDEPCODE_H_INCLUDED
#include <stdint.h>

#ifndef uint16_t
//typedef unsigned short int uint16_t;
//typedef unsigned char uint8_t;
//typedef short int int16_t;
//typedef char int8_t;
#endif

#define VT100_HEIGHT 24
#define VT100_WIDTH 80
//set the color for next written characters
void hw_setFrontColor(uint16_t col);
void hw_setBackColor(uint16_t col);

//fill an area in the display. dimensions are in characters, not pixel.
//0,0 is top left corner
//x from 0 to width-1
//y from 0 to heigth-1

void hw_fillRect(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, uint16_t col);

//move a region of the screen. start/end rows are within the scrolled region
//lines > 0 for up scroll
//lines < 0 for down scroll
void hw_scroll(uint16_t scroll_start_row,uint16_t scroll_end_row,int16_t lines);


//move cursor to x,y
void hw_cursor(uint16_t x, uint16_t y);

//write a character ch at x,y. use the default colors
void hw_drawChar(uint16_t x, uint16_t y, uint8_t ch);

//update the display memory with the frame buffer
void hw_refreshVideo(void);

#include <windows.h>
#include "wincon.h"


#define HW_BLACK   ( 0 )
#define HW_RED     ( FOREGROUND_RED )
#define HW_GREEN   ( FOREGROUND_GREEN )
#define HW_YELLOW  ( FOREGROUND_RED | FOREGROUND_GREEN )
#define HW_BLUE    ( FOREGROUND_BLUE )
#define HW_MAGENTA ( FOREGROUND_RED | FOREGROUND_BLUE )
#define HW_CYAN    ( FOREGROUND_BLUE | FOREGROUND_GREEN )
#define HW_WHITE   ( FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN )

#define HW_BG_BLACK   ( 0 )
#define HW_BG_RED     ( BACKGROUND_RED )
#define HW_BG_GREEN   ( BACKGROUND_GREEN )
#define HW_BG_YELLOW  ( BACKGROUND_RED | BACKGROUND_GREEN )
#define HW_BG_BLUE    ( BACKGROUND_BLUE )
#define HW_BG_MAGENTA ( BACKGROUND_RED | BACKGROUND_BLUE )
#define HW_BG_CYAN    ( BACKGROUND_BLUE | BACKGROUND_GREEN )
#define HW_BG_WHITE   ( BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN )


static const uint16_t hw_colors[] =
{
    HW_BLACK,
    HW_RED,
    HW_GREEN,
    HW_YELLOW,
    HW_BLUE,
    HW_MAGENTA,
    HW_CYAN,
    HW_WHITE
};

static const uint16_t hw_bg_colors[] =
{
    HW_BG_BLACK,
    HW_BG_RED,
    HW_BG_GREEN,
    HW_BG_YELLOW,
    HW_BG_BLUE,
    HW_BG_MAGENTA,
    HW_BG_CYAN,
    HW_BG_WHITE
};


#endif // HARDWAREDEPCODE_H_INCLUDED
