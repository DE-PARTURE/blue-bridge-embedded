#include "USART.h"
#include "Stdio.h"


/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   100

#define USARTz                   USART2
#define USARTz_GPIO              GPIOA
#define USARTz_CLK               RCC_APB1Periph_USART2
#define USARTz_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USARTz_RxPin             GPIO_Pin_3
#define USARTz_TxPin             GPIO_Pin_2
#define USARTz_IRQn              USART2_IRQn
#define USARTz_IRQHandler        USART2_IRQHandler
/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer1[100] = "Hello World!";
uint8_t RxBuffer1[100];
__IO uint8_t TxCounter1 = 0x00;
__IO uint8_t RxCounter1 = 0x00; 
uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
uint8_t NbrOfDataToRead1 = RxBufferSize1;
__IO uint8_t TxReady = 1;//初始状态为1

void USARTInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(USARTz_CLK, ENABLE); 
	RCC_APB2PeriphClockCmd(USARTz_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
  
  /* Configure USARTz Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USARTz_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);  

  /* Configure USARTz Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USARTz_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USARTz_GPIO, &GPIO_InitStructure); 
	
  NVIC_InitStructure.NVIC_IRQChannel = USARTz_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTz, &USART_InitStructure);
	
	USART_ITConfig(USARTz, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USARTz, USART_IT_TXE, DISABLE);
	USART_Cmd(USARTz, ENABLE);
}

void USARTz_IRQHandler(void)
{
  if(USART_GetITStatus(USARTz, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer1[RxCounter1++] = USART_ReceiveData(USARTz);

    if(RxCounter1 == NbrOfDataToRead1)
    {
      /* Disable the USARTz Receive interrupt */
      USART_ITConfig(USARTz, USART_IT_RXNE, DISABLE);
    }
  }
  
  if(USART_GetITStatus(USARTz, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USARTz, TxBuffer1[TxCounter1++]);

    if(TxCounter1 == NbrOfDataToTransfer1)
    {
      /* Disable the USARTz Transmit interrupt */
      USART_ITConfig(USARTz, USART_IT_TXE, DISABLE);
			TxReady = 1;
    }    
  }
}

void USARTSendString()
{
	while(TxReady == 0);
	NbrOfDataToTransfer1 = TxBufferSize1;//记得更新容量大小
	TxCounter1 = 0;//发送计数变量
	TxReady = 0;//Tx忙碌
	USART_ITConfig(USARTz, USART_IT_TXE, ENABLE);
	
}

