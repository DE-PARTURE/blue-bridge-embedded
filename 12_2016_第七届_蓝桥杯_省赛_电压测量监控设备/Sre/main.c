/*******************************************************************************
* 文件名：main.c
* 描  述：
* 作  者：Joseph
* 版本号：v1.0.0
* 日  期: 2020年10月13日
* 备  注：
*         2016_第七届_蓝桥杯_省赛_模拟液位检测
*		  		1、驱动编写 2、实现功能
*******************************************************************************
*/
#include "stm32f10x.h"
#include "Stdio.h"
#include "lcd.h"
#include "ADC.h"
#include "EEPROM.h"
#include "LED.h"
#include "Keyboard.h"
#include "I2C.h"
#include "USART.h"
#include "RTC.h"
#include "UI.h"

u32 TimingDelay = 0;
u8 Str[255];
u8 LEDFlag = 0;
u8 Set_Hour = 0,Set_Min = 0,Set_Sec = 0,Set_Time = 0;
u8 LEDBlingFlag = 0;
u8 UIIndex = 0;
float ADCDat = 0;
float EEDat = 0;
void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{

	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_SetPriority(SysTick_IRQn,0); //设置滴答定时器抢占优先级为0
	
	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	LEDInit();
	KeyInit();
	USARTInit();
	i2c_init();
	ADC1Init();
	RTCInit();
	Delay_Ms(200);
	
	
	while(1)
	{
		UISelect();
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

