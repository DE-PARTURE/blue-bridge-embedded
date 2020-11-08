/*
	实验说明:实现DS18B20温度扫描功能
	跳线配置:
		P4 6
		   |
		P3 6(TDQ)
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "seg.h"
#include "stdio.h"
#include "ds18b20.h"
#include "main.h"

u32 DelayTiming = 0;


int main(void)
{
	u8 str[20];
	
	float x = 0.0;
	u8 y = 0;
	u16 z = 0;
	
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	STM3210B_SEG_Init();
	SEG_DisplayValue(16,16,16);	//SEG OFF
	
//	ds18b20_init_x();
	
	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);

	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,(u8*)"    DS18B20 DEMO    ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	
	while(1){

		z = (ds18b20_read()& 0x07FF);
		x = z/16.;
		y = z/16;

		snprintf((char*)str, sizeof(str), " Temperatrue:%2.2f", x);
		LCD_DisplayStringLine(Line6,str);

		SEG_DisplayValue(y/10, y%10,12);
		
		Delay_Ms(200);
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
