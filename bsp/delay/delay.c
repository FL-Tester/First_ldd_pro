#include "delay.h"

void delay(volatile unsigned int n){
    while(n--){
        volatile unsigned int n_ms = ms_1;
        while(n_ms--);         
    }
}



void delay_init(void){
    GPT1->CR = 0;  
    GPT1->CR = 1 << 15;
    while((GPT1->CR >> 15) & 0x01); //等待复位完成
    GPT1->CR = (1<<6);

	GPT1->PR = 65;
	GPT1->OCR[0] = 0XFFFFFFFF;
	GPT1->CR |= 1<<0;	
}
void delayus(unsigned    int usdelay){
    unsigned int oldcnt, newcnt;
    unsigned long tcntvalue = 0;

    oldcnt = GPT1->CNT;
    while(1){
        newcnt = GPT1->CNT;
        if(newcnt < oldcnt){
            tcntvalue += (0xffffffff - oldcnt + newcnt);
        }else{
            tcntvalue += (newcnt - oldcnt);
        }
        if(tcntvalue >= usdelay){
            break;
        }
        oldcnt = newcnt;
    }
}
void delayms(unsigned int msdelay){
    int i = 0;
    for(i = 0; i < msdelay; i++){
        delayus(1000);
    }
}
