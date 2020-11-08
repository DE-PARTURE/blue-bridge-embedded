/*
	实验说明:ADC转换实验
	跳线配置:
		P4 4 5
		   | |
		P30 4 5(AO1/AO2)
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "adc.h"
#include "main.h"


u32 DelayTiming = 0;

//
int main(void)
{	
	
	u8 str[20];
	u16 x,y;
	
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);

	ADC_Config();

	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);

	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,(u8*)"      ADCs DEMO     ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	while(1){
		
		x = Get_ADCs(ADC_Channel_4);
		y = Get_ADCs(ADC_Channel_5);
		
		snprintf((char *)str, sizeof(str), " VRp5:%3.2fV", x/4096.*3.3);
		LCD_DisplayStringLine(Line6, str);
		snprintf((char *)str, sizeof(str), " VRp6:%3.2fV", y/4096.*3.3);
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
