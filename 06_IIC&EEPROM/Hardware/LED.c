#include "HeadFile.h"

void LEDCMD(BitAction BitVal)//Bit_SET 开 Bit_RESET 关
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_2,BitVal);
}

void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//C、D IO口组时钟使能
	//GPIOC配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_12|
														GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIOD配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	//LED全灭
	LEDCMD(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC)|0xFF00);
	LEDCMD(Bit_RESET);
}




