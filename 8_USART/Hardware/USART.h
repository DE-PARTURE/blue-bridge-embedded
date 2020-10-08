#ifndef USART_H_
#define USART_H_

#include "stm32f10x.h"
extern u8 USART_RX_Buffer[20];
void USART2_Init(u32 Bound);
void USART2_SendString(u8 *Str);



#endif
