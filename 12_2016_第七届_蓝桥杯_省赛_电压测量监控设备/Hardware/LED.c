#include "stm32f10x.h"

extern void Delay_Ms(u32 nTime);

void LEDCMD(BitAction BitVal)//Bit_RESET Bit_SET
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_2,BitVal);
}

//PD2 PC8~15
void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
																	GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	LEDCMD(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC)| 0xFF00);
	LEDCMD(Bit_RESET);
}

void LEDSetting(uint16_t Val)
{
	LEDCMD(Bit_SET);
	GPIO_Write(GPIOC,Val);
	LEDCMD(Bit_RESET);
}

void LEDBling(void)
{
	LEDSetting(0xFE00);
	Delay_Ms(200);
	LEDSetting(0xFF00);
	Delay_Ms(200);
}

