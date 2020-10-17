#ifndef  __ADC_H__
#define  __ADC_H__

#include "stm32f10x.h"

extern float AD_Data;
extern u16 ADC_Dat;

void ADC1_Init(void);
void AD_Get(void);

#endif
