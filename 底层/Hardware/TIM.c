#include "TIM.h"
#include "Buzzer.h"

u8 Flag200Ms = 0;

void TIM4Init()//20msÖÐ¶Ï
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 72-1;
  TIM_TimeBaseStructure.TIM_Prescaler = 20000-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
}

void TIM4_IRQHandler(void)
{
	static u8 Count = 0;
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		Count++;
		if(Count >= 10)
		{
			Flag200Ms = 1;
			Count = 0;
		}
		//Buzzer
		if(BuzzerCount == 0)
		{
			BuzzerOff();
		}
		else
		{
			BuzzerCount --;
		}
		
		
  }	
}
