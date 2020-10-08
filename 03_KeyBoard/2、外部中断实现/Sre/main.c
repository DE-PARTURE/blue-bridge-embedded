#include "Headfile.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断分组2，抢占:响应 = 2:2
	LEDInit();
	DelayInit();
	STM3210B_LCD_Init();
	LCD_Clear(Blue2);
	LCD_SetBackColor(Cyan);
	LCD_SetTextColor(Black);
	
	EXTIInit();
	
	
	while(1){};
}

