#include "Headfile.h"

void TIM2_ICInit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM2_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//1、初始化定时器和通道对应IO的时钟。
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//2、初始化PA1，模式为输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	//3、初始化定时器（时基设置）
  TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1 ;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	//4、初始化输入捕获通道
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;//定时器2的通道2
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//上升沿捕获
  TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//使用通道默认IC即IC2
  TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//不分频
  TIM2_ICInitStructure.TIM_ICFilter = 0x00;//不滤波
	//5、使能定时器
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);//IC初始化
	TIM_Cmd(TIM2, ENABLE);//打开定时器
	//6、如果要开启捕获中断
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
}


