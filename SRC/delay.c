//delay.c
#include"types.h"

/* Delay in microseconds */
void delay_us(u32 de_us)
{
for(de_us*=12;de_us>0;de_us--);
}

/* Delay in milliseconds */
void delay_ms(u32 de_ms)
{
for(de_ms*=12000;de_ms>0;de_ms--);
}

/* Delay in seconds */
void delay_s(u32 de_s)
{
for(de_s*=12000000;de_s>0;de_s--);
}
