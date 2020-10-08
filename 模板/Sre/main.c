#include "Headfile.h"

/** 
* @file （本文件的文件名eg：mib.h） 
* @brief （本文件实现的功能的简述）
* @version 1.1 （版本声明）
* @author （作者，eg：张三）
* @date （文件创建日期，eg：2010年12月15日）
*/


/** 滴答定时器实现延时中间变量 */
u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{
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
	
	while(1);
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
