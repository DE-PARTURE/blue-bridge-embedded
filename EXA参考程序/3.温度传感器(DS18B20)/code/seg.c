#include "stm32f10x.h"
#include "seg.h"

//
uc8 Seg7[17] = { 0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c, 0x39,0x4f,0x79,0x78,0x00}; 

void STM3210B_SEG_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

//
void SEG_DisplayValue(u8 Bit1,  u8 Bit2, u8 Bit3)
{
	u8 i = 0;	//
	u8 code_tmp = 0;

	code_tmp = Seg7[Bit3];
	for(i=0;i<8;i++){

		if(code_tmp & 0x80){
			SER_H;
		}else{
			SER_L;
		}
		SCK_H;
		code_tmp = code_tmp << 1;   
		SCK_L;
	}
	
	code_tmp = Seg7[Bit2];
	for(i=0;i<8;i++){

		if(code_tmp & 0x80){
			SER_H;
		}else{
			SER_L;
		}
		SCK_H;
		code_tmp = code_tmp << 1;   
		SCK_L;
	}	
	
	code_tmp = Seg7[Bit1];
	for(i=0;i<8;i++){

		if(code_tmp & 0x80){
			SER_H;
		}else{
			SER_L;
		}
		SCK_H;
		code_tmp = code_tmp << 1;   
		SCK_L;
	}		
	RCLK_H;
	RCLK_L;
}
