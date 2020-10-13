#include "Headfile.h"

//公式为：溢出时间Tout（单位秒）=(arr+1)(psc+1)/Tclk


//2MS = (2000)*(72)/72000000
void TIM1_PWMInit()// 500Hz
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//开启 TIM1 时钟以及复用功能时钟，配置 PA1为复用输出。
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//初始化 TIM1,设置 TIM1 的 ARR（自动重装载值） 和 PSC（预分频值）。
  TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 2000 - 1;//设置PWM频率为 1000000/2000=500Hz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	//设置 TIM1_CH1的 PWM 模式，使能 TIM1 的 CH1输出。
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse= 200;//占空比设置为10%
	
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_Pulse= 1800;//占空比设置为90%
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	//使能 TIM1。
	TIM_CtrlPWMOutputs(TIM1, ENABLE);//高级定时器输出PWM需要使用
	TIM_Cmd(TIM1,ENABLE);
	
}






