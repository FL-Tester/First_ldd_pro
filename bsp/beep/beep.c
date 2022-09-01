#include "beep.h"

void beep_init(void)
{   

    //复用为gpio
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);	
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0X10B0);

    //gpio初始化
    gpio_pin_config_t beep_config;
    beep_config.direction = GPIO_OUTPUT;
    beep_config.outputLogic = 1;
    gpio_init(GPIO5, 1, &beep_config);
}


void beep_switch(int status)
{
    if(status == ON)
        gpio_pinwrite(GPIO5, 1, 0);
	else if(status == OFF)
        gpio_pinwrite(GPIO5, 1, 1);
}
