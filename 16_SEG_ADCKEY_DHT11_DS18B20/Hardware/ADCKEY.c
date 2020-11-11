#include "stm32f10x.h"


void ADC1Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //RCC_PCLK2_Div6
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//ADCIN5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//DISABLE
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//DISABLE
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
	
	
	/* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5);//ADC_Channel_2,ADC_SampleTime_239Cycles5
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, DISABLE);
}

u16 ADCValGet(void)
{
	u16 ADCVal = 0;
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5);//ADC_Channel_2,ADC_SampleTime_239Cycles5
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==0);
	ADCVal = ADC_GetConversionValue(ADC1);
  ADC_SoftwareStartConvCmd(ADC1, DISABLE);
	
	return ADCVal;
}

u8 ADCKEYGet()
{
	u8 KeyNum = 0;//1~8
	u16 ADCVal = 0;
	
	ADCVal = ADCValGet();
	
	if(ADCVal < 50){
		KeyNum = 1;
	}else if( (ADCVal>150)&&(ADCVal<250) ){
		KeyNum = 2;
	}else if( (ADCVal>550)&&(ADCVal<650) ){
		KeyNum = 3;
	}else if( (ADCVal>1000)&&(ADCVal<1100) ){
		KeyNum = 4;
	}//...
	
	return KeyNum;
}

