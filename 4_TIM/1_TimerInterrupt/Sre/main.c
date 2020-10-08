#include "Headfile.h"

//Main Body
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Timer3InteruptInit(9999,7199);//1s
	LEDInit();
	Delay_Ms(100);
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line4 ,(unsigned char *)"    Hello,world.   ");
	LCD_Clear(Blue);
	

	while(1);
}

