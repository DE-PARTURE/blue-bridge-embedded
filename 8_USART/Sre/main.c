#include "Headfile.h"

/** 
* @file 		main.c 
* @brief 		实现响应上位机命令（发送字符1）：串口发送RTC时间
* @version	1.1
* @author 	JosephCooper
* @date 		2020年8月27日
*/

void Delay_Ms(u32 nTime);
/** 滴答定时器实现延时中间变量 */
u32 TimingDelay = 0;
/** 闹钟状态标志位 */
u8 AlarmFlag = 0;
/** 闹钟状态标志位 */
u8 USART_StringBuffer[20];

//Main Body
int main(void)
{
	u8 Index = 0;
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Delay_Ms(200);
	
	LEDInit();//LED初始化
	//关闭所有LED
	LEDCmd(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC) | 0xFF00);
	LEDCmd(Bit_RESET);
	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);

	USART2_Init(9600);
	BuzzerInit();//蜂鸣器初始化
	RTCInit(23,59,55);//实时时钟初始化
	AlarmEXITInit();
	//AlarmSet(23,59,59);
	
	while(1)
	{
		if(USART_RX_Buffer[0] == '1')
		{
			RTCtoString(USART_StringBuffer);
			USART2_SendString(USART_StringBuffer);
			//清空USART接受数据缓冲区
			for(Index = 0;Index < 20;Index ++)
			{
				USART_RX_Buffer[Index] = 0;
			}
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		}
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
