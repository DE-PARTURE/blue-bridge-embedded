#include "HeadFile.h"

u8 KeyCount = 0;

u8 KeySta[4] = {
	1, 1, 1, 1
};
u8 KeyMap[5] = {
	'A', 'B', 'C', 'D'
};

void KeyInit(){
	GPIO_InitTypeDef GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIOInitStructure);
}

void KeyScan(){
	u8 index = 0;
	static u8 KeyBuffer[4] = {
		0xFF, 0xFF, 0xFF, 0xFF
	}; 
	KeyBuffer[0] = (KeyBuffer[0] << 1) | K1;
	KeyBuffer[1] = (KeyBuffer[1] << 1) | K2;
	KeyBuffer[2] = (KeyBuffer[2] << 1) | K3;
	KeyBuffer[3] = (KeyBuffer[3] << 1) | K4;
	
	for(index = 0; index < 4; index ++){
		if(KeyBuffer[index] == 0xFF ){
			KeySta[index] = 1;
		}else if(KeyBuffer[index] == 0x00){
			KeySta[index] = 0;
		}
	}

}

void KeyDriver(){
	u8 index = 0;
	static u8 KeyBackup[4] = {
		1, 1, 1, 1
	};
	
	for(index = 0; index < 4; index ++){
		if(KeySta[index] != KeyBackup[index] ){
			KeyBackup[index] = KeySta[index];
			if(KeySta[index] == 0){
				KeyAction(KeyMap[index]);
			}
		}
	}
	
}

void KeyAction(u8 CMD){
	u8 Display;
	if(CMD == 'A'){
		KeyCount ++;
	}else if(CMD == 'B'){
		KeyCount += 2;
	}else if(CMD == 'C'){
		KeyCount += 3;
	}else if(CMD == 'D'){
		KeyCount += 4;
	}
	if(KeyCount >= 10){
		KeyCount -= 10;
	}
	Display = '0'+KeyCount;
	LCD_DisplayStringLine(Line4,&(Display));

}

