#ifndef  __USART_H__
#define  __USART_H__
#include "stm32f10x.h"



extern uint8_t TxBuffer1[]; 
extern uint8_t RxBuffer1[];
extern __IO uint8_t TxCounter1;
extern __IO uint8_t RxCounter1; 
extern uint8_t NbrOfDataToTransfer1;
extern uint8_t NbrOfDataToRead1;
extern u8 TxReady;
extern u8 TX_Flag;
extern u8 RxReady;


void USARTInit(void);
void USART2_SendString(void);

#endif
