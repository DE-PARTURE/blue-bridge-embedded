#include "Headfile.h"

int main(void)
{
	u8 i = 0;
	SysTick_Config(SystemCoreClock/1000);

	Delay_Ms(200);
	
	//STM3210B_LCD_Init();
	//LED和液晶不可同时操作
	LEDInit();
	LEDEnable(Bit_SET);
	for(i = 0; i < 9; i++){
		LEDSingleRun(i);
		Delay_Ms(100);
	} 
	LEDSingleRun(0);
	for(i = 8; i > 0; i--){
		LEDSingleRun(i);
		Delay_Ms(100);
	} 
	LEDSingleRun(0);
	for(i = 0; i < 9; i++){
		LEDRun(i);
		Delay_Ms(100);
	} 
	LEDSingleRun(0);
	for(i = 8; i > 0; i--){
		LEDRun(i);
		Delay_Ms(100);
	} 
	LEDSingleRun(0);
	LEDEnable(Bit_RESET);
	
	while(1);
}

