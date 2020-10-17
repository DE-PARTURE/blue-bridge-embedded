#include "stm32f10x.h"
#include "lcd.h"
#include "LED.h"
#include "KEY.h"                                            
#include "ADC.h"
#include "PWMOC.h"
#include "UI.h"
#include "Stdio.h"
#include "String.h"

u32 TimingDelay = 0;
u8 Str[255];

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{

	memset(Str,0,255);
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_SetPriority(SysTick_IRQn,0);
	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);

	LEDInit();
	KEYInit();
	ADC1_Init();
	TIM3_Ch1PWMInit();
	TIM1_Ch1NPWMInit();

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
