/*
	实验说明:光敏电阻实验-开关信号输出
	跳线配置:
		P4:3
		   |
		P5:3(TRDO)
	2017年4月24日 13:38:38
*/

#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"


u32 DelayTiming = 0;

//
void DO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//
int main(void)
{	
	SysTick_Config(SystemCoreClock/1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);

	DO_Config();

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

		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == Bit_SET){
			LCD_DisplayStringLine(Line7, (u8*)"       DO:High     ");
		}else{
			LCD_DisplayStringLine(Line7, (u8*)"       DO:Low      ");
		}
	}
}

//
void Delay_Ms(u32 nTime)
{
	DelayTiming = nTime;

	while(DelayTiming != 0);
}
