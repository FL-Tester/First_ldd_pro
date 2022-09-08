#include "main.h"




// /* 背景颜色索引 */
// unsigned int backcolor[10] = {
// 	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
// 	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

// }; 
	


//点灯
int main(int argv, char **argc){

    //exit_init();	
    //epit1_init(0, 66000000/2);
    //filterkey_init();
    imx6u_clkinit();
    clk_enable();
    beep_init();
    int_init();
    led_init();
    key_init();
    delay_init(); //GPT1定时器 初始化
    uart_init();
    lcd_init();	
    //初始化


//SPI协议

    unsigned short ir, als, ps;
	unsigned char state = OFF;


    while(ap3216c_init()){
            lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Check Failed!");
            delayms(500);
            lcd_show_string(30, 130, 200, 16, 16, (char*)"Please Check!        ");
            delayms(500);
        }

    while(1)					
	{
		ap3216c_readdata(&ir, &ps, &als);		/* 读取数据		  	*/
		printf("IR = %d, PS = %d, ALS = %d\r\n", ir, ps, als); 
		delayms(120);
		state = !state;
		led_switch(LED_0,state);	
	}

#if 0

// ap3216c传感器 i2c协议测试
    unsigned short ir, als, ps;
	unsigned char state = OFF;


    tftlcd_dev.forecolor = LCD_RED;	
    lcd_show_string(30, 50, 200, 16, 16, (char*)"ALPHA-IMX6U IIC TEST");  
	lcd_show_string(30, 70, 200, 16, 16, (char*)"AP3216C TEST");  
	lcd_show_string(30, 90, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(30, 110, 200, 16, 16, (char*)"2019/3/26");  

    while(ap3216c_init()){
        lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Check Failed!");
		delayms(500);
		lcd_show_string(30, 130, 200, 16, 16, (char*)"Please Check!        ");
		delayms(500);
    }


    lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Ready!");  
    lcd_show_string(30, 160, 200, 16, 16, (char*)" IR:");	 
	lcd_show_string(30, 180, 200, 16, 16, (char*)" PS:");	
	lcd_show_string(30, 200, 200, 16, 16, (char*)"ALS:");	
	tftlcd_dev.forecolor = LCD_BLUE;

    while(1)					
	{
		ap3216c_readdata(&ir, &ps, &als);		/* 读取数据		  	*/
		lcd_shownum(30 + 32, 160, ir, 5, 16);	/* 显示IR数据 		*/
        lcd_shownum(30 + 32, 180, ps, 5, 16);	/* 显示PS数据 		*/
        lcd_shownum(30 + 32, 200, als, 5, 16);	/* 显示ALS数据 	*/ 
		delayms(120);
		state = !state;
		led_switch(LED_0,state);	
	}




//驱动 lcd
    unsigned char index = 0;
	unsigned char state = OFF;
    tftlcd_dev.forecolor = LCD_RED;
    while(1){

        lcd_clear(backcolor[index]);
		delayms(1); 	  
        /*
        * @description		: 显示一串字符串
        * @param - x		: 起始坐标点X轴。
        * @param - y		: 起始坐标点Y轴。
        * @param - width 	: 字符串显示区域长度
        * @param - height	: 字符串显示区域高度
        * @param - size	: 字体大小
        * @param - p		: 要显示的字符串首地址
        * @return 			: 无
        */
		lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPHA IMX6U"); 	
		lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
		lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM@ALIENTEK");      					 
		lcd_show_string(10, 130, 240, 12, 12,(char*)"2019/8/14");	      					 
	    index++;
		if(index == 10)
			index = 0;      
		state = !state;
		led_switch(LED_0,state);
		delayms(1000);

    }

//自定义stdio 串口打印

    printf("hello world\n");
    int a , b;
    while(1){        
        delayms(500);
        printf("输入两个整数，使用空格隔开:");
		scanf("%d %d", &a, &b);					 		/* 输入两个整数 */
		printf("\r\n数据%d + %d = %d\r\n\r\n", a, b, a+b);	/* 输出两个数相加的和 */
    }


//uart 收发实验

    unsigned char a = 0;

    while(1){
        //uart发送hello world 500ms
        //uart_send_bytes("hello world\r\n", 13);
        //delayms(500);
        //接收一个字符 并且发送接收的字符
        uart_send_bytes("请输入1个字符:");
		a=uartrecvonebyte();
		uart_send_one_byte(a);	//回显功能
		uart_send_bytes("\r\n");
    }



    int key_value = 0;
    int led_count = 0;

    //初始化状态位 状态位在切换的时候 直接取反即可
    unsigned char led_state = OFF;
    unsigned char beep_state = OFF;



// 高精度延时
    while(1)
    {
        static unsigned char state = 0;
        led_switch(LED_0, state);
        state = !state;
        delayms(500);
        
    }


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


    return 0;

}
// main end!


