#ifndef RTC_H_
#define RTC_H_

#include "stm32f10x.h"
#define AlaFlag 0//用于TFT刷新时辨识
#define SecFlag 1//用于TFT刷新时辨识

extern u8 HourAla;
extern u8 MinAla;
extern u8 SecAla;
void RTCInit(u8 Hour,u8 Min,u8 Sec);
void RTCtoTFT(u8 Flag);
void AlarmSet(u8 Hour,u8 Min,u8 Sec);
void AlarmEXITInit(void);

#endif
