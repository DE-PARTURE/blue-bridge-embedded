#include "Headfile.h"

/** USART接受数据缓冲区 */
u8 USART_RX_Buffer[20];

void USART2_Init(u32 Bound)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//串口时钟及GPIOA时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//串口复位
	USART_DeInit(USART2);
	//GPIO设置 PA2复用推挽输出 PA3浮空
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//串口参数初始化
	USART_InitStructure.USART_BaudRate = Bound;//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//收发双模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_Init(USART2,&USART_InitStructure);
	//初始化NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART2,ENABLE);//使能串口
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启USART2接收中断
}

void USART2_SendString(u8 *Str)
{
	u8 Index = 0;
	while(Str[Index] != 0)
	{
		USART_SendData(USART2,Str[Index]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == 0);
		Index ++;
	}
}

void USART2_IRQHandler(void)
{
	u16 Temp;
	u8 USART_RX_Cnt = 0;
	if(USART_GetFlagStatus(USART2,USART_IT_RXNE) == 1)
	{
		USART_ClearFlag(USART2,USART_IT_RXNE);
		Temp = USART_ReceiveData(USART2);
		if(Temp == '\n')
		{
			USART_RX_Cnt = 0;
			USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);
		}
		else
		{
			USART_RX_Buffer[USART_RX_Cnt++] = Temp;
		}
	}
}

