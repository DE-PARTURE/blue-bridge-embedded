#ifndef KEY_H_
#define KEY_H_

extern u8 KeyMap[5];
#define K1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define K2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define K3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define K4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)

void KeyInit(void);
void KeyScan(void);
void KeyDriver(void);
void KeyAction(u8 CMD);

#endif
