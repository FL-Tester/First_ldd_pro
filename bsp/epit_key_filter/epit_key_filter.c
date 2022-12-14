#include "epit_key_filter.h"





void filterkey_init(void)
{
    gpio_pin_config_t key_filter_config;

    //初始化io复用
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);

    //配置电气属性
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);

    //初始化gpio为中断
    key_filter_config.direction = GPIO_INPUT;
    key_filter_config.interruptMode =kGPIO_IntFallingEdge;
    key_filter_config.outputLogic = 1;
    gpio_init(GPIO1, 18, &key_filter_config);

    //gic中断使能
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);

    //注册中断服务函数
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, 
							   (system_irq_handler_t)gpio1_16_31_irqhandler, 
							   NULL);
    gpio_enableint(GPIO1, 18);		/* 使能GPIO1_IO18的中断功能 */

	filtertimer_init(66000000/100);	/* 初始化定时器,10ms */                     
}

void filtertimer_init(unsigned int value)
{
	EPIT1->CR = 0;	//先清零
	
	/*
     * CR寄存器:
     * bit25:24 01 时钟源选择Peripheral clock=66MHz
     * bit15:4  0  1分频
     * bit3:	1  当计数器到0的话从LR重新加载数值
     * bit2:	1  比较中断使能
     * bit1:    1  初始计数值来源于LR寄存器值
     * bit0:    0  先关闭EPIT1
     */
	EPIT1->CR = (1<<24 | 1<<3 | 1<<2 | 1<<1);

	/* 计数值    */
	EPIT1->LR = value;
	
	/* 比较寄存器，当计数器值和此寄存器值相等的话就会产生中断 */
	EPIT1->CMPR	= 0;	
	
	GIC_EnableIRQ(EPIT1_IRQn);	/* 使能GIC中对应的中断 */
	
	/* 注册中断服务函数		    */
	system_register_irqhandler(EPIT1_IRQn, (system_irq_handler_t)filtertimer_irqhandler, NULL);	
}

/*
 * @description		: 关闭定时器
 * @param 			: 无
 * @return 			: 无
 */
void filtertimer_stop(void)
{
	EPIT1->CR &= ~(1<<0);	/* 关闭定时器 */
}

/*
 * @description		: 重启定时器
 * @param - value	: 定时器EPIT计数值
 * @return 			: 无
 */
void filtertimer_restart(unsigned int value)
{
	EPIT1->CR &= ~(1<<0);	/* 先关闭定时器 */
	EPIT1->LR = value;		/* 计数值 			*/
	EPIT1->CR |= (1<<0);	/* 打开定时器 		*/
}

/*
 * @description		: 定时器中断处理函数 
 * @param			: 无
 * @return 			: 无
 */
void filtertimer_irqhandler(void)
{ 
	static unsigned char state = OFF;

	if(EPIT1->SR & (1<<0)) 					/* 判断比较事件是否发生			*/
	{
		filtertimer_stop();					/* 关闭定时器 				*/
		if(gpio_pinread(GPIO1, 18) == 0)	/* KEY0 				*/
		{
			state = !state;
			beep_switch(state);				/* 反转蜂鸣器 				*/
		}
	}
		
	EPIT1->SR |= 1<<0; 						/* 清除中断标志位 				*/
}

/*
 * @description		: GPIO中断处理函数
 * @param			: 无
 * @return 			: 无
 */
void gpio1_16_31_irqhandler(void)
{ 
	/* 开启定时器 */
	filtertimer_restart(66000000/100);

	/* 清除中断标志位 */
	gpio_clearintflags(GPIO1, 18);
}