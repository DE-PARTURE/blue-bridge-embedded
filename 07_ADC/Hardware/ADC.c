#include "Headfile.h"

void ADCInit()
{
	//PinInit
	GPIO_InitTypeDef GPIOInitStructure;
	ADC_InitTypeDef ADCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOB,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC时钟6分频->14MHz(不能超过14MHz)
	
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOB,&GPIOInitStructure);
	//ADCInit
	ADC_DeInit(ADC1);//初始化ADC1
	ADCInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADCInitStructure.ADC_ScanConvMode = DISABLE;//单通道模式
	ADCInitStructure.ADC_ContinuousConvMode = DISABLE;//单次转换模式
	ADCInitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发方式
	ADCInitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC数据右对齐
	ADCInitStructure.ADC_NbrOfChannel = 1;//顺序进行规则转换的通道数目
	ADC_Init(ADC1,&ADCInitStructure);
	ADC_Cmd(ADC1,ENABLE);//使能ADC1控制器
	
	ADC_ResetCalibration(ADC1);//ADC1复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位校准结束
	ADC_StartCalibration(ADC1);//ADC1开始校准
	while(ADC_GetCalibrationStatus(ADC1));//等待开始校准结束
}

u16 GetADC()
{
	u16 Temp;
	//设定指定ADC的规则组通道，设置转化顺序和采样时间
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);
	//设定通道1的采样顺序值为1，采样时间为239.5个周期（(239.5+12.5)/14=252/14=18us）
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//使能软件转换功能
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换完成
	Temp = ADC_GetConversionValue(ADC1);//获取转换结果
	ADC_SoftwareStartConvCmd(ADC1,DISABLE);//关闭软件转换功能
	return Temp;
}

u16 GetADCAverage(u8 Times)//获取指定次数的AD值的平均值
{
	u32 TempVal = 0;
	u8 Index = 0;
	for(Index = 0; Index < Times;Index ++)
	{
		TempVal += GetADC();
		Delay_Ms(5);
	}
	return TempVal/Times;
}

