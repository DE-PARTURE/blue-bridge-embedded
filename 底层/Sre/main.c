#include "stm32f10x.h"
#include "lcd.h"
#include "LED.h"
#include "Buzzer.h"
#include "ADC.h"
#include "EEPROM.h"
#include "i2c.h"
#include "PWMIC.h"
#include "PWMOC.h"
#include "USART.h"
#include "KEY.h"
#include "TIM.h"
#include "RTC.h"
#include "Stdio.h"
#include "String.h"

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{
	u8 Index = 0;
	u8 Str[255];
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_SetPriority(SysTick_IRQn,0);//滴答定时器设置抢占优先级0
	
	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	LEDInit();
	BuzzerInit();
	TIM4Init();
	ADC1Init();
	KEYInit();
	i2c_init();
	USARTInit();
	RTCInit();
	PWMOCInit(10000);//注意防止定时器溢出
	PWMICInit();
	
	Index = EERead(0x01);
	Index++;
	EEWrite(0x01,Index);
	BuzzerOn(100);
	
	while(1)
	{
		if(Flag200Ms)
		{
			Flag200Ms = 0;
			AD_Get();
			sprintf((char *)Str, "AD:%.2fV                ", ADCVal);
			LCD_DisplayStringLine(Line1, Str);
			sprintf((char *)Str, "0x01:%d                ", Index);
			LCD_DisplayStringLine(Line2, Str);
			sprintf((char *)Str, "%.2d:%.2d:%.2d", Hour,Min,Sec);
			LCD_DisplayStringLine(Line3, Str);
			sprintf((char *)Str, "TIM2Freq:%dHz        ", TIM2Freq);
			LCD_DisplayStringLine(Line4, Str);
			sprintf((char *)Str, "Duty:%d%%            ", Duty);
			LCD_DisplayStringLine(Line5, Str);
			USARTSendString();
		}
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
