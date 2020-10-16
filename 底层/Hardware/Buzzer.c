#include "Buzzer.h"

extern void Delay_Ms(u32 nTime);
u8 BuzzerCount = 0;

void BuzzerInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void BuzzerOn(u32 Ms)//
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_4,Bit_RESET);
	BuzzerCount = Ms/20;
}

void BuzzerOff()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_4,Bit_SET);
}


