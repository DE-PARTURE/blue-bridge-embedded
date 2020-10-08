#include "Headfile.h"


void Delay_Ms(u32 nTime);
u32 TimingDelay = 0;
u8 AlarmFlag = 0;

//Main Body
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);

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
	RTCInit(23,59,55);//实时时钟初始化
	AlarmEXITInit();
	AlarmSet(23,59,59);
	while(1);
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
