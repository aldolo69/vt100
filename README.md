# VT100
Lbrary to develop a VT100 terminal

In vt100.h there is the original copyright. I've stripped all the hardware dependent code from vt100.cpp. If you want to use the code on whatever hardware or operating system you have to rewrite hardwaredepcode.cpp. Now the code show the output in the Windows terminal.

void hw_setFrontColor(uint16_t col);
void hw_setBackColor(uint16_t col);
void hw_fillRect(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, uint16_t col);
void hw_scroll(uint16_t scroll_start_row,uint16_t scroll_end_row,int16_t lines);
void hw_cursor(uint16_t x, uint16_t y);
void hw_drawChar(uint16_t x, uint16_t y, uint8_t ch);

These are the required functions. hw_refreshVideo() redraw the whole display but it is not strictly required if you use real hardware for the output.
