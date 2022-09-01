#pragma once

#include "beep.h"
#include "delay.h"
#include "gpio.h"
#include "int.h"

//有一个很奇怪的现象 必须beep.h 放在int.h前面才能通过编译 就很离谱
// 一点合理的解释： 在gcc编译的时候，如果文件a依赖于文件b，那么编译的时候必须把a放前面，b放后面。




void exit_init(void);						/* 中断初始化 */
void gpio1_io18_irqhandler(void); 			/* 中断处理函数 */


