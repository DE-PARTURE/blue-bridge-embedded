#ifndef  __LIS302DL_H__
#define  __LIS302DL_H__
#include "stm32f10x.h"


void LIS302DL_Write(u8 Addr,u8 Val);
u8 LIS302DL_Read(u8 Addr);
void LIS302DL_Init(void);
void LIS302DL_DataRead(void);


extern u8 LIS302DL_X;
extern u8 LIS302DL_Y;
extern u8 LIS302DL_Z;

#endif


