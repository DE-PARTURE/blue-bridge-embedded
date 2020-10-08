#include "HeadFile.h"

void KeyInit(){
	GPIO_InitTypeDef GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_Init(GPIOB,&GPIOInitStructure);
}



