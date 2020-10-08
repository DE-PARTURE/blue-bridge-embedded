#include "HeadFile.h"

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);

	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);

	LCD_DisplayStringLine(Line4 ,(unsigned char *)"    Buzzer Test.   ");
	Delay_Ms(1000);
	BuzzerInit();
	
	while(1){
		BuzzerSet;
		Delay_Ms(1000);
		BuzzerReset;
		Delay_Ms(1000);
		
	}
}


