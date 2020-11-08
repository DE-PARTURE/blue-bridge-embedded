/*
	实验说明:读LIS302DL传感器X、Y、Z轴向寄存器
	跳线配置:
		P2短接,同时保证PA4/5/6/7引脚不被其它资源占用
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "main.h"
#include "mems.h"
#include "i2c.h"
#include "math.h"
u32 DelayTiming = 0;

int main(void)
{
	u8 str[20];
	
	u8 *ptr;
		
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);

	i2c_init();
	LIS302DL_Config();
	
	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);

	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,(u8*)"     MEMS DEMO      ");
	//
	if(LIS302DL_Check() == 1){
		LCD_DisplayStringLine(Line3, (u8 *)" MEMS STATUS: OK");
	}else{
		LCD_DisplayStringLine(Line3, (u8 *)" MEMS STATUS: ERROR");				
	}

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);
	
	
	while(1){
		
		ptr = Lis302DL_Output();
				
		snprintf((char *)str, sizeof(str), " X Reg:%d    ", ptr[0]);
		LCD_DisplayStringLine(Line6,str);
		snprintf((char *)str, sizeof(str), " Y Reg:%d    ", ptr[1]);
		LCD_DisplayStringLine(Line7,str);
		snprintf((char *)str, sizeof(str), " Z Reg:%d    ", ptr[2]);
		LCD_DisplayStringLine(Line8,str);
				
		Delay_Ms(200);
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
