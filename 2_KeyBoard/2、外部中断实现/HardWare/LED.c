#include "Headfile.h"

u8 i = 0;//LED索引

u16 _crol_(u16 val,u8 n)//16位数循环左移
{
	u16 buf;
  n = n % 16;
  buf = val >> ( 16 - n );
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
	GPIO_InitTypeDef GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIOInitStructure);
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIOInitStructure);
	
	LEDEnable(Bit_SET);
	LEDSingleRun(0);
	LEDEnable(Bit_RESET);
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

void LEDAction1(){
	LEDEnable(Bit_SET);
	LEDSingleRun(0);
	LEDRun(1);
	LEDRun(3);
	LEDRun(5);
	LEDRun(7);
	LEDEnable(Bit_RESET);
}

void LEDAction2(){
	LEDEnable(Bit_SET);
	LEDSingleRun(0);
	LEDRun(2);
	LEDRun(4);
	LEDRun(6);
	LEDRun(8);
	LEDEnable(Bit_RESET);
}

void LEDAction3(){
	LEDEnable(Bit_SET);
	LEDSingleRun(0);	
	LEDRun(1);
	LEDRun(3);
	LEDRun(5);
	LEDRun(7);
	LEDRun(2);
	LEDRun(4);
	LEDRun(6);
	LEDRun(8);
	LEDEnable(Bit_RESET);
}
void LEDReset(void){
	LEDEnable(Bit_SET);
	LEDSingleRun(0);
	LEDEnable(Bit_RESET);
}
