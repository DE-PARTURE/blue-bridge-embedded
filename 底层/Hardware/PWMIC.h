#ifndef  __PWMIC_H__
#define  __PWMIC_H__
#include "stm32f10x.h"
extern __IO uint32_t TIM2Freq;
extern __IO uint32_t Duty;

void PWMICInit(void);

#endif
