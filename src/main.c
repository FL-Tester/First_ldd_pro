#include "main.h"

//点灯
int main(int argv, char **argc)
{
    imx6u_clkinit();
    clk_enable();
    beep_init();
    int_init();
    led_init();
    key_init();
    // exit_init();	
    // epit1_init(0, 66000000/2);
    filterkey_init();


    while(1)
    {
        delay(100);
    }



#if 0
    int key_value = 0;
    int led_count = 0;

    //初始化状态位 状态位在切换的时候 直接取反即可
    unsigned char led_state = OFF;
    unsigned char beep_state = OFF;



//1.点灯
    while(1)
    {
        
        led_switch(0, OFF);
        delay(100);
    }

//2.蜂鳴器
    while(1)
    {
        static unsigned char state = 0;
        state = !state;
        led_switch(LED_0, state);
        delay(100);
    } 

  


//3.按键检测 蜂鸣器回应 led闪烁运行标志
    while(1)
    {
        //读取按键 蜂鸣器启动
        key_value = key_getvalue();

        //为了拓展性 可以添加按键判断
        if(key_value)
        {
            switch(key_value)
            {
                case KEY_0:
                    beep_state = !beep_state;
                    beep_swtich(beep_state);
                    break;
            }
        }

        //运行标志 led闪烁
        led_count++;
        if(led_count == 50)
        {
            led_count = 0;
            led_state = !led_state;
            led_switch(0, led_state);
        }
        delay(10);
    }  
#endif  


}
// main end!


