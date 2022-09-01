#include "key.h"


void key_init(void)
{   
    gpio_pin_config_t key_config;

    //复用为gpio1 IO18
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);	
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0XF080);
    
    //gpio初始化
    key_config.direction = GPIO_INPUT;
    gpio_init(GPIO1, 18, &key_config);
}




//延时去抖动 标志位互斥
int key_getvalue(void)
{
    int ret = 0;
    static unsigned char release_flag = 0;

    if((release_flag ==1) && (gpio_pinread(GPIO1, 18) == 0))
    {
        delay(10);
        release_flag = 0;
        if(gpio_pinread(GPIO1, 18) == 0)
            ret = KEY_0;
    }
    else if(gpio_pinread(GPIO1, 18) == 1)
    {
        release_flag = 1;
        ret = KEY_NONE;
    }

    return ret;
}
