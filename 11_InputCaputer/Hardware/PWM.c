#include "Headfile.h"

//公式为：溢出时间Tout（单位秒）=(arr+1)(psc+1)/Tclk


//2MS = (2000)*(72)/72000000
void TIM3_PWMInit()// 500Hz
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//1）开启 TIM3 时钟以及复用功能时钟，配置 PC8、PC9 为复用输出。
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//2）设置 TIM3_CH3、TIM3_CH4 重映射到 PC8、PC9 上。
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	//3）初始化 TIM3,设置 TIM3 的 ARR（自动重装载值） 和 PSC（预分频值）。
  TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 2000 - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	//4）设置 TIM3_CH3、TIM3_CH4 的 PWM 模式，使能 TIM3 的 CH3、CH4 输出。
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//5）使能 TIM3。
	TIM_Cmd(TIM3,ENABLE);
	
	
}





