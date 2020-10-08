#include "Headfile.h"

int main(void)
{
	float DataADC;
	u8 String[20];
	//滴答定时器设定
	SysTick_Config(SystemCoreClock/1000);
	LEDInit();
	//关闭LED
	LEDCmd(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC) | 0xFF00);
	LEDCmd(Bit_RESET);
	//LCD初始化
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	//ADC初始化
	ADCInit();
	
	while(1)
	{
		DataADC = GetADCAverage(10);//获取10次AD值的平均值
		sprintf((char *)String, "ADC = %.2f V", DataADC * 3.3 / 4096);//12位ADC对3.3V量化
		LCD_DisplayStringLine(Line5,String);//显示3.3V量化后的ADC值
	}
}


