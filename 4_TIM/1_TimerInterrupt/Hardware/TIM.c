#include "Headfile.h"
u8 TimCount = 0;
//Tout = (ARR+1)(PSC+1)/Tclk 时间计算公式
void Timer3InteruptInit(u16 arr, u16 psc){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//（1）、TIM3 时钟使能。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3时钟
	//（2）、初始化定时器参数,设置自动重装值，分频系数，计数方式等
	TIM_TimeBaseInitStructure.TIM_Period = arr;//自动重装值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//分频系数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数方式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	//（3）、设置 TIM3_DIER 允许更新中断。
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//（4）、TIM3 中断优先级设置。
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	//（5）、允许 TIM3 工作，也就是使能 TIM3。
	TIM_Cmd(TIM3,ENABLE);
	
}
//（6）、编写中断服务函数。
void TIM3_IRQHandler(void){
	if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update) == SET){
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
	TimCount ++;
	LCD_DisplayStringLine(Line4 ,&(TimCount));
	
}

