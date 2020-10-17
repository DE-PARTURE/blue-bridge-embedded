#ifndef  __UI_H__
#define  __UI_H__

#include "stm32f10x.h"

extern u8 Mode;//AUTO:1,MANU:2
extern u8 UIIndex;//Data:0,Para:1
//Para
extern u8 PA6Para;//Duty
extern u8 PA7Para;//Duty

void UISelect(void);



#endif
