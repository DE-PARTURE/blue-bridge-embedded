#include "Headfile.h"

/** 用于TFT显示闹钟时间字符串的中间变量 */
u8 HourAla = 0;
u8 MinAla = 0;
u8 SecAla = 0;

//实时时钟配置函数
void RTCInit(u8 Hour,u8 Min,u8 Sec)
{
	//时钟中断配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//闹钟中断配置
	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;  //闹钟中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //比RTC全局中断的优先级高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	//时钟电源配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);//使能电源时钟和备份区域时钟
	
	PWR_BackupAccessCmd(ENABLE);//取消备份区写保护
	BKP_DeInit();//复位备份区域
	RCC_LSICmd(ENABLE);//开启LSI震荡器
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);//等待时钟使能完毕
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI); //选择LSI作为时钟源
	RCC_RTCCLKCmd(ENABLE);//使能RTC时钟
	
	//RTC配置
	RTC_WaitForLastTask();//等待最近一次对 RTC 寄存器的写操作完成
	RTC_WaitForSynchro();//等待APB1时钟和RTC时钟同步
	RTC_WaitForLastTask();
	RTC_EnterConfigMode();//进入配置模式
	RTC_WaitForLastTask();
	RTC_SetPrescaler(40000-1);//设置预分频系数
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC,ENABLE);//使能RTC秒中断
	RTC_WaitForLastTask();
	RTC_SetCounter(Hour*3600 + Min*60 + Sec);//设置时间
	RTC_ExitConfigMode();//退出配置模式
}
//闹钟外部中断配置
void AlarmEXITInit()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}
//闹钟设置函数
void AlarmSet(u8 Hour,u8 Min,u8 Sec)
{
	RTC_EnterConfigMode();//进入配置模式
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_ALR,ENABLE);
	RTC_WaitForLastTask();
	RTC_SetAlarm(Hour*3600 + Min*60 + Sec);
	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成 
	RTC_ExitConfigMode();//退出配置模式
	HourAla = Hour;MinAla = Min;SecAla = Sec;
}
//秒中断服务函数
void RTC_IRQHandler(void)
{
		static u8 Cnt = 0;
		if(RTC_GetITStatus(RTC_IT_SEC) == 1)//秒中断
		{
			RTC_ClearITPendingBit(RTC_IT_SEC);//清除秒中断标志
			
			if(AlarmFlag == 1)//监控蜂鸣器响3Sec
			{
				Cnt ++;
				
				if(Cnt > 3)
				{
					BuzzerReset;//关闭Buzzer
					AlarmFlag = 0;
					RTCtoTFT(AlaFlag);//刷新时间
					Cnt = 0;
				}
				else
				{
					RTCtoTFT(AlaFlag);//刷新时间
				}
			}
			else
			{
				RTCtoTFT(SecFlag);//刷新时间
			}
		}	
}
//闹钟中断服务函数
void RTCAlarm_IRQHandler(void)
{     
	if(RTC_GetITStatus(RTC_IT_ALR) == 1)//闹钟中断
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);//清除闹钟中断
		AlarmFlag = 1;
		BuzzerSet;
	}
	EXTI_ClearITPendingBit(EXTI_Line17);
	RTC_WaitForLastTask();
	RTC_ClearITPendingBit(RTC_IT_ALR);
	RTC_WaitForLastTask();
}
//LCD刷新函数
void RTCtoTFT(u8 Flag)
{
	u32 Time = 0;
	u8 Hour = 0,Min = 0,Sec = 0;
	u8 str[20];
	Time = RTC_GetCounter();
	RTC_WaitForLastTask();
	if(Time >= (23*3600 + 59*60 + 59))
	{
		RTC_SetCounter(0);
		RTC_WaitForLastTask();
	}
	
	Hour = Time / 3600;
	Min = (Time % 3600) / 60;
	Sec = (Time % 3600) % 60;
		
	sprintf((char *)str,"%.2d:%.2d:%.2d", Hour, Min, Sec);
	LCD_DisplayStringLine(Line5,str);
	
	if(Flag == AlaFlag)
	{
		if(AlarmFlag == 1)//闹钟启动
		{
			sprintf((char *)str,"AlarmTime:%.2d:%.2d:%.2d", HourAla, MinAla, SecAla);
			LCD_DisplayStringLine(Line6,str);//显示闹钟时间字符串
		}
		else if(AlarmFlag == 0)//闹钟结束
		{
			LCD_ClearLine(Line6);//清除闹钟时间字符串
		}
	}
}

void RTCtoString(u8 *str)
{
	u32 Time = 0;
	u8 Hour = 0,Min = 0,Sec = 0;
	Time = RTC_GetCounter();
	RTC_WaitForLastTask();
	if(Time >= (23*3600 + 59*60 + 59))
	{
		RTC_SetCounter(0);
		RTC_WaitForLastTask();
	}
	
	Hour = Time / 3600;
	Min = (Time % 3600) / 60;
	Sec = (Time % 3600) % 60;
	sprintf((char *)str,"%.2d:%.2d:%.2d\n", Hour, Min, Sec);

}

