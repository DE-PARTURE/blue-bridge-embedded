#include "Headfile.h"

/** 
* @file main.c
* @brief 实现测量PA7输入(PWM2)矩形波频率占空比
* @version 1.0
* @author JosephCooper
* @date 2020年11月7日
*/


/** 滴答定时器实现延时中间变量 */
u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{
	u8 str[20];
	memset(str,0,sizeof(str)/sizeof(str[0]));//字符数组初始化
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
	TIM3_CC2Config();
	BuzzerInit();//蜂鸣器初始化
	
	while(1)
	{
		snprintf((char *)str, sizeof(str), " DTY:%d%%   ", DutyCycle);
		LCD_DisplayStringLine(Line6, str);
		
		snprintf((char *)str, sizeof(str), " FRQ:%dHz  ",Frequency);
		LCD_DisplayStringLine(Line7, str);
		
		Delay_Ms(200);
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
