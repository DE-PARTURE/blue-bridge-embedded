#include "HeadFile.h"

void BuzzerInit(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//开启AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);//将PB4映射为普通IO
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	BuzzerReset;
}
