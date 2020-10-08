#include "Headfile.h"

void Timer3InteruptInit(u16 arr, u16 psc){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	TIM_Cmd(TIM3,ENABLE);
	
}

void TIM3_IRQHandler(void){
	if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update) == SET){
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
	
	
}

void Timer3PWMInit(u16 arr, u16 psc){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//(1)开启 TIM3 时钟以及复用功能时钟，配置 PB8、PB9 为复用输出。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC,ENABLE);
	//(2)、设置 TIM3_CH3  TIM3_CH4 重映射到 PB8、PB9 上。
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//通过Datasheet可知PC8和PC9对应TIM3PWM输出为完全重映射
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//(3)、初始化 TIM3,设置 TIM3 的 ARR 和 PSC。
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	//PC8 PWM输出设置TIM3_CH3
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;							//PWM输出模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//输出极性高
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);												
	//(4)、设置 TIM3_CH3 的 PWM 模式，使能 TIM3 的 CH3 输出。
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//PC9 PWM输出设置TIM3_CH4
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	//(4)、设置 TIM3_CH4 的 PWM 模式，使能 TIM3 的 CH4 输出。
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//
	TIM_Cmd(TIM3,ENABLE);
}

