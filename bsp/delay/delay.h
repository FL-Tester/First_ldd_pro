#pragma once

#include "imx6ul.h"
#define ms_1 0x7ff





void delay(volatile unsigned int n);//循环延时

//GPT1定时器 延时
void delay_init(void);
void delayus(unsigned    int usdelay);
void delayms(unsigned	 int msdelay);

