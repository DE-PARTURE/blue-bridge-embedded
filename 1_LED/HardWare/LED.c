#include "Headfile.h"

u16 _crol_(u16 val,u8 n)//16Î»ÊýÑ­»·×óÒÆ
{
  n = n % 16;
  u16 buf = val >> ( 16 - n );
  val = val << n;
  val |= buf;
  return val;
	//val --->	0xFEFF
	//n   --->	3
	//0xFEFF->	1111 1110 1111 1111
	//buf ---> 	0000 0000 0000 0111
	//val --->	1111 0111 1111 1000
	//val --->  1111 0111 1111 1111
}

void LEDInit(){
	GPIO_InitTypeDef GPIOInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIOInitStruct);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIOInitStruct);
		
}

void LEDEnable(BitAction BitVal){
		GPIO_WriteBit(GPIOD,GPIO_Pin_2,BitVal);
}

void LEDSingleRun(u8 index){
	if(index != 0){
	GPIO_Write(GPIOC,_crol_(0xFEFF,index - 1) );
	}else{
		GPIO_Write(GPIOC,0xFFFF);
	}
}

void LEDRun(u8 index){
	if(index != 0){
	GPIO_Write(GPIOC,(_crol_(0xFEFF,index - 1) 
		& GPIO_ReadOutputData(GPIOC)) );
	}else{
		GPIO_Write(GPIOC,0xFFFF);
	}
}

