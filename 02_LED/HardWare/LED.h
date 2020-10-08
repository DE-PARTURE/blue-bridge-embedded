#ifndef LED_H_
#define LED_H_

void LEDInit(void);
void LEDEnable(BitAction BitVal);//Bit_RESET = 0,Bit_SET
void LEDSingleRun(u8 index);
void LEDRun(u8 index);
u16 _crol_(u16 val,u8 n);

#endif
