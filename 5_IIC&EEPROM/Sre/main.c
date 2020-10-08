#include "HeadFile.h"

//Main Body
int main(void)
{
	u8 Str[20];
	u8 Dat = 0;
	
	
	SysTick_Config(SystemCoreClock/1000);//DelayInit
	LEDInit();
	IICInit();
	Delay_Ms(200);

	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	Dat = EERead(0x01);
	sprintf((char *)Str,"Data = %d",Dat);
	EEWrite(0x01, (++Dat));
	
	LCD_DisplayStringLine(Line5,Str);
	while(1);
}

