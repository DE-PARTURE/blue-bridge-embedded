#include "LED.h"

void LEDCMD(BitAction BitVal)//Bit_RESET
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_2,BitVal);
}

void LEDInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| 
																		GPIO_Pin_12|GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	LEDCMD(Bit_SET);
	GPIO_Write(GPIOC,0xFF00);
	LEDCMD(Bit_RESET);
}

void LEDSetting(uint16_t PortVal)
{
	LEDCMD(Bit_SET);
	GPIO_Write(GPIOC,PortVal);
	LEDCMD(Bit_RESET);
}

