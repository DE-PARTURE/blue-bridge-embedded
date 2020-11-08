#ifndef __ADC_H
#define __ADC_H

#define ADC_BUFF_LEN	50


#include "stm32f10x.h"

void ADC_Config(void);
u16 Get_ADCs(u8 channel);
u16 Get_Filter(u8 channel);

#endif
