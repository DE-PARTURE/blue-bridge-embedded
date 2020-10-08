#include "Headfile.h"

int main(void)
{
	DelayInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	STM3210B_LCD_Init();//LCD初始化
	LCD_Clear(Blue2);
	LCD_SetBackColor(Cyan);
	LCD_SetTextColor(Black);
	LEDInit();//关闭全部LED
	KeyInit();//按键初始化
	TaskInit(&Action1);//任务1初始化
	TaskInit(&Action2);//任务2初始化
	TaskInit(&Action3);//任务3初始化
	TaskInit(&Action4);//任务4初始化
	TIM3Init(999,7199);//100ms定时器中断
	
	while(1){
		
		KeyScan();
		KeyDriver();
	}
}

