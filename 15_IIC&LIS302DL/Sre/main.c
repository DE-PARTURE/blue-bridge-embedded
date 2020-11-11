#include "Headfile.h"

/** 
* @file main.c
* @brief 读取三轴加速度计X、Y、Z轴原始数据并显示
* @version 1.0
* @author JosephCooper
* @date 2020年11月9日
*/


/** 滴答定时器实现延时中间变量 */
u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);


//Main Body
int main(void)
{
	u8 Str[20];
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
	i2c_init();
	LIS302DL_Init();
	
	while(1)
	{
		LIS302DL_DataRead();
		sprintf((char*)Str,"X:%d Y:%d Z:%d         ",LIS302DL_X,LIS302DL_Y,LIS302DL_Z);
		LCD_DisplayStringLine(Line0,Str);
		Delay_Ms(200);
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

