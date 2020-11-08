/*
	实验说明:实现数码管静态显示功能
	跳线配置:
		P3:1 2 3(SER RCK SCK)
		   | | |
		P4:1 2 3
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "seg.h"


u32 DelayTiming = 0;

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	STM3210B_SEG_Init();
	SEG_DisplayValue(16,16,16);	//SEG OFF

	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);

	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,(u8*)"      SEG DEMO      ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	
	LCD_DisplayStringLine(Line6,(u8*)"  SEG display:567   ");
	SEG_DisplayValue(5,6,7);

	while(1){
		;
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
