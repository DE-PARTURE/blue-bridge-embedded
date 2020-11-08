/*
	实验说明:实现湿度测量功能
	跳线配置:
		P4 7
		   |
		P3 7(HDQ)
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "seg.h"
#include "stdio.h"
#include "dht11.h"
#include "main.h"

u32 DelayTiming = 0;

int main(void)
{
	u8 str[20];
	
	u32 z = 0;
	
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	STM3210B_SEG_Init();
	SEG_DisplayValue(16,16,16);	//SEG OFF
	
	dht11_init();
	
	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);

	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,(u8*)"     DHT11 DEMO     ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	
	while(1){

		z = dht11_read();

		snprintf((char *)str, sizeof(str), " Moisture:%2d%%", z>>24);
		LCD_DisplayStringLine(Line6,str);
		snprintf((char *)str, sizeof(str), " Temperature:%3d", (z>>8)&0xff);
		LCD_DisplayStringLine(Line7,str);

		SEG_DisplayValue(((z>>8)&0xff)/10, ((z>>8)&0xff)%10, 12);
		
		Delay_Ms(200);
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
