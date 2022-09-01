#pragma once

#include "delay.h"
#include "gpio.h"

void key_init(void);
int key_getvalue(void);


//按键值 枚举类型 就是宏定义集合
enum keybalue{
    KEY_NONE = 0,
    KEY_0,
    KEY_1,
};