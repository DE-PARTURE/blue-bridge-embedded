#include "stm32f10x.h"
#include "Stdio.h"
#include "lcd.h"
#include "dht11.h"
#include "ADCKEY.h"
#include "ds18b20.h"
#include "LED.h"
#include "SEG.h"



u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{
	u8 KEYVal = 0;
	//u16 ADC1Val = 0;
	float DS_TemVal = 0;
	unsigned int DHT_Val = 0;
	u8 Str[20];
	
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_SetPriority(SysTick_IRQn,0);
	Delay_Ms(200);
	
	

	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	

	LEDInit();
//	ADC1Init();
	SEGInit();
	ds18b20_init_x();
	dht11_init();

	
	while(1)
	{
//		KEYVal = ADCKEYGet();
//		SEGSet(0,0,KEYVal);
		//
		DS_TemVal = ds18b20_read()*0.0625;
		sprintf((char *)Str,"Tem:%.2f            ",DS_TemVal);
		LCD_DisplayStringLine(Line3,Str);
		//
		DHT_Val = dht11_read();
		sprintf((char *)Str, " Humidity: %2d%%", DHT_Val>>24); 
		LCD_DisplayStringLine(Line4, Str); 
		sprintf((char *)Str, " Temperature: %2dC", (DHT_Val>>8)&0xff); 
		LCD_DisplayStringLine(Line5, Str);
		
		Delay_Ms(2000);
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
