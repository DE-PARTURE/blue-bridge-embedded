/**
  ******************************************************************************
  * @file    I2S/SPI_I2S_Switch/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
extern u32 TimingDelay;

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup I2S_SPI_I2S_Switch
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay--;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_Switch_IRQHandler(void)
{
}*/
//7、编写中断服务函数
__IO uint16_t IC2ReadValue1 = 0, IC2ReadValue2 = 0,IC2ReadValue_LOW = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
__IO uint32_t TIM2Freq = 0;
__IO uint32_t TIM2Duty = 0;
u8 TIM2FreqReady = 0;
void TIM2_IRQHandler(void)
{ 
  if(TIM_GetITStatus(TIM2, TIM_IT_CC2) == SET) 
  {
    /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
    if(CaptureNumber == 0)
    {
      /* Get the Input Capture value */
      IC2ReadValue1 = TIM_GetCapture2(TIM2);
      CaptureNumber = 1;
			//设置下降沿捕获
			TIM_OC2PolarityConfig(TIM2,TIM_OCPolarity_Low);
    }
		else if(CaptureNumber == 1)
		{
			IC2ReadValue_LOW = TIM_GetCapture2(TIM2);
			CaptureNumber = 2;
			//设置上升沿捕获
			TIM_OC2PolarityConfig(TIM2,TIM_OCPolarity_High);
		}
    else if(CaptureNumber == 2)
    {
      /* Get the Input Capture value */
      IC2ReadValue2 = TIM_GetCapture2(TIM2); 
      
      /* Capture computation */
      if (IC2ReadValue2 > IC2ReadValue1)
      {
        Capture = (IC2ReadValue2 - IC2ReadValue1); 
      }
      else
      {
        Capture = ((0xFFFF - IC2ReadValue1) + IC2ReadValue2);
				
      }
      /* Frequency computation */ 
			TIM2Duty = ( (IC2ReadValue_LOW-IC2ReadValue1)*100 ) / Capture;
      TIM2Freq = 1000000 / Capture;//定时器经过72分频后的频率
      CaptureNumber = 0;
			TIM2FreqReady = 1;
			TIM_SetCounter(TIM2,0);
    }
		
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
