#include "Headfile.h"

/** 
* @file 		main.c 
* @brief 		实现捕获PWM端的输出
* @version  1.0
* @author   JosephCooper
* @date     2020.09.03
*/


/** 滴答定时器实现延时中间变量 */
u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{
	u8 TIM3_PWMDuty = 0;
	u8 TIM3_PWMDir = 0;
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Delay_Ms(200);
	
	LEDInit();//LED初始化
	//关闭所有LED
	LEDCmd(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC) | 0xFF00);
	LEDCmd(Bit_RESET);
	
//LCD和LED的引脚有冲突所以不使用
//	STM3210B_LCD_Init();
//	LCD_Clear(Blue);
//	LCD_SetBackColor(Blue);
//	LCD_SetTextColor(White);
	
	BuzzerInit();//蜂鸣器初始化
	TIM3_PWMInit();//TIM3_PWM初始化
	LEDCmd(Bit_SET);
	while(1)
	{
		//6）修改 TIM3_CCR3、TIM3_CCR4 来控制占空比。
		TIM_SetCompare3(TIM3,TIM3_PWMDuty*20);
		TIM_SetCompare4(TIM3,(101-TIM3_PWMDuty)*20);
		Delay_Ms(30);
		
		if(TIM3_PWMDuty > 100)
		{
			TIM3_PWMDir = 0;
		}
		if(TIM3_PWMDuty == 0)
		{
			TIM3_PWMDir = 1;
		}
		
		if(TIM3_PWMDir)
		{
			TIM3_PWMDuty ++;
		}
		else
		{
			TIM3_PWMDuty --;
		}
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
