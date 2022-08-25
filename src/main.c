#include "main.h"


int main(int argv, char **argc)
{
    clk_enable();
    led_init();

    while(1)
    {
        led_switch(0, ON);
        delay(100);
        led_switch(0, OFF);
        delay(100);
    }
}