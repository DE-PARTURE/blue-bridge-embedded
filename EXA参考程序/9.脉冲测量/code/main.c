/*
	实验说明:脉冲测量功能
	跳线配置:
		P4	7
			|
		P5	7
		
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "main.h"
#include "timer.h"

//from _it.c
extern __IO uint16_t DutyCycle;
extern __IO uint32_t Frequency;


u32 DelayTiming = 0;

//
int main(void)
{	
	
	u8 str[20];
	
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	
	Tim3_Ch_Config();

	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);

	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,(u8*)"     PUSLE DEMO     ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	while(1){
		
		snprintf((char *)str, sizeof(str), " DTY:%d%%   ", DutyCycle);
		LCD_DisplayStringLine(Line6, str);
		
		snprintf((char *)str, sizeof(str), " FRQ:%.1fKHz  ",Frequency/1000.);
		LCD_DisplayStringLine(Line7, str);
		
		Delay_Ms(200);
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
