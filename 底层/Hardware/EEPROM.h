#ifndef  __EEPROM_H__
#define  __EEPROM_H__
#include "stm32f10x.h"

void EEWrite(u8 Addr,u8 Val);
u8 EERead(u8 Addr);


#endif
