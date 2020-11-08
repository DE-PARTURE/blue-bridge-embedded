/*
	实验说明:光敏电阻实验-模拟输出
	跳线配置:
		P4 4
		   |
		P5 4(TRAO)
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
	u16 tmp = 0;
	
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

	LCD_DisplayStringLine(Line1,(u8*)"    R-Photo DEMO    ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	while(1){
		
		tmp = Read_ADC();
		snprintf((char *)str, sizeof(str), " R-P:%.2fK  ", tmp/(4096.-tmp)*10);//(U2/U1)*R1=R2
		LCD_DisplayStringLine(Line6, str);
		Delay_Ms(200);
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
