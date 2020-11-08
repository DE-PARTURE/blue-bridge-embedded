#include "stm32f10x.h"
#include "adc.h"

static u16 adc_buff[ADC_BUFF_LEN];

//
void ADC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	/* ADC1 regular channels configuration */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
}

//
u16 Get_ADCs(u8 channel)
{
	
	u16 ADC_Val = 0;
	
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	ADC_Val = ADC_GetConversionValue(ADC1);
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
	
	return ADC_Val;
}

//
u16 Get_Filter(u8 channel)
{
	u16 tmp;
	u8 i = 0,j = 0;
	
	for(i=0; i<ADC_BUFF_LEN; i++){
		adc_buff[i] = Get_ADCs(channel);
	}

	for(i=0; i<=ADC_BUFF_LEN-1; i++){
		for(j=0; j<	ADC_BUFF_LEN-i-1; j++){
			if(adc_buff[j+1] < adc_buff[j]){
				tmp = adc_buff[j+1];
				adc_buff[j+1] = adc_buff[j];
				adc_buff[j] = tmp;
			}
		}
	}

	if(ADC_BUFF_LEN % 2 == 0){
		return(adc_buff[ADC_BUFF_LEN/2-1] + adc_buff[ADC_BUFF_LEN/2])/2;
	}else{
		return(adc_buff[ADC_BUFF_LEN/2]);
	}
}
