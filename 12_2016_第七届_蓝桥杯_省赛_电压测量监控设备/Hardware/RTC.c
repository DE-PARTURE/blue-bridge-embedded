#include "stm32f10x.h"
#include "Stdio.h"
#include "lcd.h"
#include "USART.h"



u8 HH = 23,MM = 59,SS = 55;
u8 Hour = 0, Min = 0, Sec = 0;
extern u8 Set_Time;
u32 Time = 0;
extern u8 Str[];
extern u8 TX_Flag;

void RTCInit()
{
	NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable the LSI OSC */
  RCC_LSICmd(ENABLE);
  /* Wait till LSI is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(40000);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* To output second signal on Tamper pin, the tamper functionality
       must be disabled (by default this functionality is disabled) */

  /* Enable the RTC Second Output on Tamper Pin */
	
	RTC_SetCounter(HH * 3600 + MM * 60 + SS);//…Ë÷√RTC ±º‰
	RTC_WaitForLastTask();

}

void RTC_IRQHandler(void)
{
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
		Time = RTC_GetCounter();
		RTC_WaitForLastTask();
		if(Time == (23*3600 + 59*60 + 59))
		{
			RTC_SetCounter(0);
			RTC_WaitForLastTask();
		}
		Hour = Time/3600;
		Min = (Time % 3600) / 60;
		Sec = Time % 60;
		
		if(Time == Set_Time)
		{
			TX_Flag = 1;
		}
    /* Clear Interrupt pending bit */
    RTC_ClearITPendingBit(RTC_FLAG_SEC);
  }
}


