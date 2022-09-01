#pragma once
#include "imx6ul.h"



//输入输出方向
typedef  enum _gpio_pin_direction{
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1
}gpio_pin_direction_t;

typedef  enum _gpio_pin_value{
    GPIO_LOW = 0,
    GPIO_HIGH = 1
}gpio_pin_value_t;



typedef enum _gpio_interrupt_mode
{
    kGPIO_NoIntmode = 0U, 				/* 无中断功能 */
    kGPIO_IntLowLevel = 1U, 			/* 低电平触发	*/
    kGPIO_IntHighLevel = 2U, 			/* 高电平触发 */
    kGPIO_IntRisingEdge = 3U, 			/* 上升沿触发	*/
    kGPIO_IntFallingEdge = 4U, 			/* 下降沿触发 */
    kGPIO_IntRisingOrFallingEdge = 5U, 	/* 上升沿和下降沿都触发 */
} gpio_interrupt_mode_t;

typedef struct{
    gpio_pin_direction_t direction;         /* GPIO方向:输入还是输出 */
    uint8_t outputLogic;                   /* 如果是输出的话，默认输出电平 */
    gpio_interrupt_mode_t interruptMode;    /* 中断方式 */
}gpio_pin_config_t;






void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config);
void gpio_pinwrite(GPIO_Type *base, int pin, int value);
int gpio_pinread(GPIO_Type *base, int pin);

void gpio_intconfig(GPIO_Type* base, unsigned int pin, gpio_interrupt_mode_t pin_int_mode);
void gpio_enableint(GPIO_Type* base, unsigned int pin);
void gpio_disableint(GPIO_Type* base, unsigned int pin);
void gpio_clearintflags(GPIO_Type* base, unsigned int pin);







