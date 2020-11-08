#ifndef __BUTTON_H
#define __BUTTON_H

#include "stm32f10x.h"

#define BTN_BUFF_LEN	50

u16 Read_Btn(void);
u8 Scan_Btn(void);

#endif

