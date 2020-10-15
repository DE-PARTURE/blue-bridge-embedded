#include "stm32f10x.h"
#include "Stdio.h"
#include "String.h"
#include "lcd.h"
#include "ADC.h"
#include "EEPROM.h"
#include "LED.h"
#include "Keyboard.h"
#include "I2C.h"
#include "USART.h"
#include "RTC.h"

extern u8 Str[];
extern u8 LEDFlag;
extern u8 Hour, Min, Sec;
extern u8 Set_Hour,Set_Min,Set_Sec,Set_Time;
extern u8 LEDBlingFlag;
extern u8 UIIndex;
u8 UISwitchFlag = 0;
u8 TimeSetIndex = 0;
extern float ADCDat;
extern float EEDat;
extern void Delay_Ms(u32 nTime);


void FlagScan()
{
	u8 EEDat_S;
	//定时发送
	if(TX_Flag){
		memset(TxBuffer1,0x00,sizeof(uint8_t)*255);//清空发送
		sprintf((char *)TxBuffer1,"%.2f+%.1f+%.2d%.2d%.2d\n",
								ADCDat,EEDat,Set_Hour,Set_Min,Set_Sec);
		USART2_SendString();
		TX_Flag = 0;
	}
	//串口接收查询
	if(RxBuffer1[0] == 'k'){
		if(RxBuffer1[1] == '0'){
			if(RxBuffer1[2] == '.'){
					RxCounter1 = 0x00;
					EEDat_S = RxBuffer1[3]- '0';
					EEWrite(0x01,EEDat_S);
					memset(TxBuffer1,0x00,sizeof(uint8_t)*255);//清空发送
					sprintf((char *)TxBuffer1,"ok\n");
					USART2_SendString();
					memset(RxBuffer1,0x00,sizeof(uint8_t)*255);//清空接收
			}
		}
	}
	//LED
	if(LEDBlingFlag & LEDFlag){
		LEDBling();
	}
	//KEY
	//切换到UI2
	if(K2_Count == 1){
		if(UISwitchFlag == 1)
		{
			LCD_Clear(Blue);//切换UI
			UIIndex = 1;//UI2
			UISwitchFlag = 0;
		}else if(K3_Count > 0){
			//选择时、分、秒
			if(TimeSetIndex < 2){
				TimeSetIndex ++;
			}else{
				TimeSetIndex = 0;//0时 1分 2秒
			}
			K3_Count = 0;
		}else if(K4_Count > 0){
			//调整时间
			if(TimeSetIndex == 0){
				if(Set_Hour < 23){
					Set_Hour++;
				}else{
					Set_Hour = 0;
				}
			}else if(TimeSetIndex == 1){
				if(Set_Min < 59){
					Set_Min++;
				}else{
					Set_Min = 0;
				}
			}else if(TimeSetIndex == 2){
				if(Set_Sec < 59){
					Set_Sec++;
				}else{
					Set_Sec = 0;
				}
			}
			K4_Count = 0;
		}
	}
	//切换到UI1
	if(K2_Count > 1){
		if(UISwitchFlag == 1)
		{
			LCD_Clear(Blue);//切换UI
			UIIndex = 0;//UI1
		}
		Set_Time = Set_Hour*3600+Set_Min*60+Set_Sec;
		K2_Count = 0;
		TimeSetIndex = 0;
	}
	//
}
//--数据刷新
void DataUpdata()
{ 
	ADCDat = AD_Get();
	ADCDat = ADCDat*3.3/4096;
	
	EEDat = EERead(0x01);
	EEDat /= 10;
	
	if(ADCDat > 3.3 * EEDat){
		LEDBlingFlag = 1;
	}else{
		LEDBlingFlag = 0;
	}
}

//UI--显示
void UI1()
{
	//ADC
	sprintf((char *)Str,"V1:%.2fV                   ",ADCDat);
	LCD_DisplayStringLine(Line2,Str);
	//EE
	sprintf((char *)Str,"k:%.1f                     ",EEDat);
	LCD_DisplayStringLine(Line3,Str);
	//LED
	if(LEDFlag){
		sprintf((char *)Str,"LED:ON               ");
	}else{
		sprintf((char *)Str,"LED:OFF              ");
	}
	LCD_DisplayStringLine(Line4,Str);
	//Time
	sprintf((char *)Str,"%.2d:%.2d:%.2d               ",Hour,Min,Sec);
	LCD_DisplayStringLine(Line5,Str);

}
//UI--设置
void UI2()
{
	sprintf((char *)Str,"       Setting       ");
	LCD_DisplayStringLine(Line3,Str);
	sprintf((char *)Str,"      %.2d-%.2d-%.2d      ",Set_Hour,Set_Min,Set_Sec);
	LCD_DisplayStringLine(Line5,Str);
}

void UISelect()
{
	DataUpdata();
	if(UIIndex == 0){
		UI1();
	}else if(UIIndex == 1){
		UI2();
	}
	FlagScan();
}

