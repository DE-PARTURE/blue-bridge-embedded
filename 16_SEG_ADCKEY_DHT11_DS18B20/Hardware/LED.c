#include "stm32f10x.h"

void LEDCMD(BitAction BitVal)//PD2//Bit_RESET
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_2,BitVal);
}

void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|
																	GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	LEDCMD(Bit_SET);
	GPIO_Write(GPIOC,0xFFFF);
	LEDCMD(Bit_RESET);
	
}
//PC8~PC15
void LEDSetting(u16 Val)
{
	LEDCMD(Bit_SET);
	GPIO_Write(GPIOC,Val);
	LEDCMD(Bit_RESET);
}

