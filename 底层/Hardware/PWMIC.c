#include "PWMIC.h"



__IO uint16_t IC2ReadValue1 = 0, IC2ReadValue2 = 0, IC2ReadValueLow = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
__IO uint32_t TIM2Freq = 0;
__IO uint32_t Duty = 0;


//PA1
void PWMICInit(void)
{
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler = 72;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
  
	TIM_Cmd(TIM2, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);

}

void TIM2_IRQHandler(void)
{ 
  if(TIM_GetITStatus(TIM2, TIM_IT_CC2) == SET) 
  {
    /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
    if(CaptureNumber == 0)
    {
      /* Get the Input Capture value */
      IC2ReadValue1 = TIM_GetCapture2(TIM2);
      CaptureNumber = 1;
			TIM_OC2PolarityConfig(TIM2,TIM_OCPolarity_Low);
    }
		else if(CaptureNumber == 1)
		{
			IC2ReadValueLow = TIM_GetCapture2(TIM2);
			TIM_OC2PolarityConfig(TIM2,TIM_OCPolarity_High);
			CaptureNumber = 2;
		}
    else if(CaptureNumber == 2)
    {
      /* Get the Input Capture value */
      IC2ReadValue2 = TIM_GetCapture2(TIM2); 
      
      /* Capture computation */
      if (IC2ReadValue2 > IC2ReadValue1)
      {
        Capture = (IC2ReadValue2 - IC2ReadValue1); 
      }
      else
      {
        Capture = ((0xFFFF - IC2ReadValue1) + IC2ReadValue2); 
      }
      /* Frequency computation */ 
      TIM2Freq = 1000000 / Capture;
			Duty = ((IC2ReadValueLow-IC2ReadValue1)*100)/Capture;
			TIM_SetCounter(TIM2,0);
      CaptureNumber = 0;
    }
  }
}
