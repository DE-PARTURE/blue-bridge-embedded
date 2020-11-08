#ifndef INPUTCAPTURE_H_
#define INPUTCAPTURE_H_

#include "stm32f10x.h"
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM2_CC2Config(void);

extern __IO uint16_t DutyCycle;
extern __IO uint32_t Frequency;

#endif
