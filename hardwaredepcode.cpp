
#include "hardwaredepcode.h"
#include <iostream>
using namespace std;

char memoryBufferChar[VT100_HEIGHT][VT100_WIDTH];
char memoryBufferForeColor[VT100_HEIGHT][VT100_WIDTH];
char memoryBufferBackColor[VT100_HEIGHT][VT100_WIDTH];

uint16_t hwForeColor;
uint16_t hwBackColor;
uint16_t hwXCursor;
uint16_t hwYCursor;


void hw_setFrontColor(uint16_t col)
{
    hwForeColor=col;
}
void hw_setBackColor(uint16_t col)
{
    hwBackColor=col;
}
void hw_fillRect(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, uint16_t col)
{
    for(int ix=0; ix<dx; ix++)
    {
        for(int iy=0; iy<dy; iy++)
        {
            memoryBufferChar[y+iy][x+ix]=' ';
            memoryBufferForeColor[y+iy][x+ix]=col;
            memoryBufferBackColor[y+iy][x+ix]=col;
        }
    }



}


//0 based row/col
//lines > 0 for scroll down
void hw_scroll(uint16_t scroll_start_row,uint16_t scroll_end_row,int16_t lines)
{

    int itotline=scroll_end_row-scroll_start_row;


    if(lines>0) //up
    {
        if(itotline<=lines)
            return;

        for(int iLine=0; iLine<itotline; iLine++)
        {
            for(int ix=0; ix<VT100_WIDTH; ix++)
            {
                memoryBufferChar[scroll_start_row+iLine][ix]=
                    memoryBufferChar[scroll_start_row+iLine+lines][ix];
                memoryBufferForeColor[scroll_start_row+iLine][ix]=
                    memoryBufferForeColor[scroll_start_row+iLine+lines][ix];
                memoryBufferBackColor[scroll_start_row+iLine][ix]=
                    memoryBufferBackColor[scroll_start_row+iLine+lines][ix];
            }

        }
    }
    else//down
    {
        lines = - lines;
        if(itotline<=lines)
            return;
        for(int iLine=0; iLine<itotline; iLine++)
        {
            for(int ix=0; ix<VT100_WIDTH; ix++)
            {
                memoryBufferChar[scroll_end_row-iLine-1][ix]=
                    memoryBufferChar[scroll_end_row-iLine-lines-1][ix];
                memoryBufferForeColor[scroll_end_row-iLine-1][ix]=
                    memoryBufferForeColor[scroll_end_row-iLine-lines-1][ix];
                memoryBufferBackColor[scroll_end_row-iLine-1][ix]=
                    memoryBufferBackColor[scroll_end_row-iLine-lines-1][ix];
            }

        }

    }




}





void hw_cursor(uint16_t x, uint16_t y)
{
    hwXCursor=x;
    hwYCursor=y;
}

void hw_drawChar(uint16_t x, uint16_t y, uint8_t ch)
{
    memoryBufferChar[y][x]=ch;
    memoryBufferForeColor[y][x]=hwForeColor;
    memoryBufferBackColor[y][x]=hwBackColor;
}





void hw_refreshVideo()
{
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD coord;


    for(int iy=0; iy<VT100_HEIGHT; iy++)
    {

        coord.X=0;
        coord.Y=iy;
        SetConsoleCursorPosition(hstdout,coord);
        for(int ix=0; ix<VT100_WIDTH; ix++)
        {
            unsigned long i;
            SetConsoleTextAttribute( hstdout, memoryBufferForeColor[iy][ix] | memoryBufferBackColor[iy][ix] );
            cout << memoryBufferChar[iy][ix];
            //WriteConsoleOutputCharacter(hstdout,&memoryBufferChar[iy][ix],1,coord,&i);

        }
    }

}
