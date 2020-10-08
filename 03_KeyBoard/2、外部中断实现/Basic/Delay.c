#include "Headfile.h"

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

void DelayInit(void){	
	SysTick_Config(SystemCoreClock/1000);
}
