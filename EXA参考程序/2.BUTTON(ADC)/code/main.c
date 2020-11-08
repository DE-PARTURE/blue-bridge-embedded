/*
	实验说明:实现ADC键盘扫描功能
	跳线配置:
		P4 5
		   |
		P5 5(AKEY)
	程序说明：电源电压出线波动情况下，适当调整按键输出电压范围
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "seg.h"
#include "adc.h"
#include "stdio.h"
#include "button.h"


u32 DelayTiming = 0;


int main(void)
{
	u8 str[20];
	u8 key_val = 0;
	
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	STM3210B_SEG_Init();
	SEG_DisplayValue(16,16,16);	//SEG OFF

	ADC_Config();

	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);

	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,(u8*)"    BUTTON DEMO     ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	
	while(1){

		snprintf((char*)str, sizeof(str), "  Button ADC:%04X", Read_Btn());
		LCD_DisplayStringLine(Line6,str);
		
		key_val = Scan_Btn();
		
		if(key_val != 0){
			SEG_DisplayValue(16, 16, key_val);
			snprintf((char*)str, sizeof(str), "  Button Value:%d", key_val);
			LCD_DisplayStringLine(Line7,str);
		}
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
