#include "config.h"

char Sec = 0;
char Min = 0;
char Hour = 0;
uint8_t Start_Flag = 0;
uint8_t EXTI_Status = 0;
uint8_t String[20];
uint32_t TimingDelay = 0;

void Close_Fucker(void);
void SetTime(void);
void LCD_USER_Init(void);
void EXTI_USER_Init(void);
void GPIO_USER_Init(void);
void Timer_Config(uint32_t InterTime);
void DisplayTime(uint8_t RealSec, uint8_t RealMin, uint8_t RealHour);

int main()
{
	GPIO_USER_Init();
	LCD_USER_Init();
	EXTI_USER_Init();
	Timer_Config(Time_1ms);
	Close_Fucker();
	
	while(1)
	{
		DisplayTime(Sec, Min, Hour);
		SetTime();
	}
}

void Timer_Config(uint32_t InterTime)
{
	SysTick_Config(SystemCoreClock / InterTime); 
}

void DisplayTime(uint8_t RealSec, uint8_t RealMin, uint8_t RealHour)
{
	uint8_t HHour, LHour, HMin, LMin, HSec, LSec;
	
	Start_Flag = 1;
	LCD_DisplayStringLine(Line1,"                   ");
	LCD_DisplayStringLine(Line1,"    DisplayTime    ");
	while(1)
	{
		HHour = Hour / 10;
		LHour = Hour % 10;
		HMin = Min / 10;
		LMin = Min % 10;
		HSec = Sec / 10;
		LSec = Sec % 10;
		
		sprintf(String,"    %d%d : %d%d : %d%d",HHour, LHour, HMin, LMin, HSec, LSec);
		LCD_DisplayStringLine(Line4, String);
		if(EXTI_Status == 1)
		{
			EXTI_Status = 0;
			break;
		}
	}
}

void SetTime()
{
	uint8_t HHour, LHour, HMin, LMin, HSec, LSec;
	
	Start_Flag = 0;
	LCD_DisplayStringLine(Line1,"                   ");
	LCD_DisplayStringLine(Line1,"      SetHour      ");
	LCD_DisplayStringLine(Line4,"                   ");
	HHour = Hour / 10;
	LHour = Hour % 10;		
	sprintf(String,"%s%d%d Hour","       ",HHour, LHour);
	LCD_DisplayStringLine(Line4, String);
	while(1)
	{
		if(EXTI_Status == 2)
		{
			EXTI_Status = 0;
			Hour++;
			if(Hour == 24)
			{
				Hour = 0;
			}
			HHour = Hour / 10;
			LHour = Hour % 10;		
			sprintf(String,"%s%d%d Hour","       ",HHour, LHour);
			LCD_DisplayStringLine(Line4, String);
		}
		if(EXTI_Status == 3)
		{
			EXTI_Status = 0;
			Hour--;
			if(Hour == 255)
			{
				Hour = 23;
			}
			HHour = Hour / 10;
			LHour = Hour % 10;		
			sprintf(String,"%s%d%d Hour","       ",HHour, LHour);
			LCD_DisplayStringLine(Line4, String);
		}
		if(EXTI_Status == 1)
		{
			EXTI_Status = 0;
			break;
		}
	}
	LCD_DisplayStringLine(Line1,"                   ");
	LCD_DisplayStringLine(Line1,"      SetMin       ");
	LCD_DisplayStringLine(Line4,"                   ");
	HMin = Min / 10;
	LMin = Min % 10;		
	sprintf(String,"%s%d%d Min","       ", HMin, LMin);
	LCD_DisplayStringLine(Line4, String);
	while(1)
	{
		if(EXTI_Status == 2)
		{
			EXTI_Status = 0;
			Min++;
			if(Min == 60)
			{
				Min = 0;
			}
			HMin = Min / 10;
			LMin = Min % 10;		
			sprintf(String,"%s%d%d Min","       ", HMin, LMin);
			LCD_DisplayStringLine(Line4, String);
		}
		if(EXTI_Status == 3)
		{
			EXTI_Status = 0;
			Min--;
			if(Min == 255)
			{
				Min = 59;
			}
			HMin = Min / 10;
			LMin = Min % 10;		
			sprintf(String,"%s%d%d Min","       ", HMin, LMin);
			LCD_DisplayStringLine(Line4, String);
		}
		if(EXTI_Status == 1)
		{
			EXTI_Status = 0;
			break;
		}
	}
	LCD_DisplayStringLine(Line1,"                   ");
	LCD_DisplayStringLine(Line1,"      SetSec       ");
	HSec = Sec / 10;
	LSec = Sec % 10;
	sprintf(String,"%s%d%d Sec","       ", HSec, LSec);
	LCD_DisplayStringLine(Line4, String);
	while(1)
	{
		if(EXTI_Status == 2)
		{
			EXTI_Status = 0;
			Sec++;
			if(Sec == 60)
			{
				Sec = 0;
			}
			HSec = Sec / 10;
			LSec = Sec % 10;
			sprintf(String,"%s%d%d Sec","       ", HSec, LSec);
			LCD_DisplayStringLine(Line4, String);
		}
		if(EXTI_Status == 3)
		{
			EXTI_Status = 0;
			Sec--;
			if(Sec == 255)
			{
				Sec = 59;
			}
			HSec = Sec / 10;
			LSec = Sec % 10;
			sprintf(String,"%s%d%d Sec","       ", HSec, LSec);
			LCD_DisplayStringLine(Line4, String);
		}
		if(EXTI_Status == 1)
		{
			EXTI_Status = 0;
			break;
		}
	}
}

void GPIO_USER_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void EXTI_USER_Init()
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);

	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);

	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void LCD_USER_Init()
{
	STM3210B_LCD_Init();
	
	LCD_SetTextColor(White);
	LCD_SetBackColor(Black);
	LCD_Clear(Black);
}

void Delay_Ms(uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void Close_Fucker()
{
	
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
	GPIO_SetBits(GPIOC, GPIO_Pin_All);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
