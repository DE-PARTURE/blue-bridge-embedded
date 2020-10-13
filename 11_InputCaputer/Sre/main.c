#include "Headfile.h"

/** 
* @file 		main.c 
* @brief 		实现PA1捕获PA9、PA10端的输出,显示频率和占空比
* @version  1.0
* @author   JosephCooper
* @date     2020.10.09
*/


/** 滴答定时器实现延时中间变量 */
u32 TimingDelay = 0;
extern __IO uint32_t TIM2Freq;
extern u8 TIM2FreqReady;
extern __IO uint32_t TIM2Duty;

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{
	uint32_t i = 0;
	u8 Str[200];
	uint32_t TIM2Freq_BP = 0;
	uint32_t TIM2Duty_BP = 0;
	memset(Str,0x00,sizeof(Str));//清空数组
	
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Delay_Ms(200);
	
	LEDInit();//LED初始化
	//关闭所有LED
	LEDCmd(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC) | 0xFF00);
	LEDCmd(Bit_RESET);
	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	BuzzerInit();//蜂鸣器初始化
	TIM2_ICInit();
	TIM1_PWMInit();//TIM1_PWM初始化
	

	while(1)
	{
		if(TIM2FreqReady)
		{
			TIM2FreqReady = 0;
			if( (TIM2Freq!=TIM2Freq_BP) || (TIM2Duty!=TIM2Duty_BP) )
			{
				TIM2Freq_BP = TIM2Duty;
				TIM2Duty_BP = TIM2Freq;
				sprintf((char*)Str,"TIM2Freq:%dHz           ", TIM2Freq);
				LCD_DisplayStringLine(Line2,Str);
				sprintf((char*)Str,"TIM2Duty:%d%%           ", TIM2Duty);
				LCD_DisplayStringLine(Line3,Str);
				for(i=0; i<500000; i++);//刷新延迟
			}
		}

	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
