#ifndef VT100_H_INCLUDED
#define VT100_H_INCLUDED


#include "hardwaredepcode.h"

void vt100_init(void (*send_response)(char *str));
void vt100_putc(uint8_t ch);
void vt100_puts(const char *str);


#endif // VT100_H_INCLUDED
