#include <stm32f10x.h>

#define SCK_H GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define SCK_L GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define SER_H GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define SER_L GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define RCK_H GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RCK_L GPIO_ResetBits(GPIOA,GPIO_Pin_2)
//0~F
u8 Seg7[17] = { 0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,
									0x07,0x7f,0x6f,0x77,0x7c, 0x39,0x4f,0x79,0x78,0x00}; 

void SEGSet(u8 Val1,u8 Val2,u8 Val3)
{
	u8 i = 0;
	u8 Val = 0;
	
	SCK_L;
	
	Val = Seg7[Val3];
	for(i = 0; i < 8; i++)
	{
		if(Val & 0x80){
			SER_H;
		}else{
			SER_L;
		}
		
		SCK_H;
		Val <<= 1;
		SCK_L;
	}
	
	Val = Seg7[Val2];
	for(i = 0; i < 8; i++)
	{
		if(Val & 0x80){
			SER_H;
		}else{
			SER_L;
		}

		SCK_H;
		Val <<= 1;
		SCK_L;
	}
	
	Val = Seg7[Val1];
	for(i = 0; i < 8; i++)
	{
		if(Val & 0x80){
			SER_H;
		}else{
			SER_L;
		}
		
		SCK_H;
		Val <<= 1;
		SCK_L;
	}

	RCK_H;
	RCK_L;
}
									
									
//PA1¡¢2¡¢3 //SER RCK SCK
void SEGInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SEGSet(17,17,17);
}

