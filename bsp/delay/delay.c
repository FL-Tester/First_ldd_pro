#include "delay.h"

void delay(volatile unsigned int n)
{
    
    while(n--)
    {
        volatile unsigned int n_ms = ms_1;
        while(n_ms--);         
    }
}