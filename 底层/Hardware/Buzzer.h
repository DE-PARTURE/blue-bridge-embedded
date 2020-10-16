#ifndef  __BUZZER_H__
#define  __BUZZER_H__
#include "stm32f10x.h"
extern u8 BuzzerCount;


void BuzzerInit(void);
void BuzzerOn(u32 Ms);
void BuzzerOff(void);


#endif
