#pragma once


#include "led.h"
#include "imx6ul.h"
#include "int.h"
void epit1_init(unsigned int frac, unsigned int value);
void epit1_irqhandler(void);

