#include "stm32f10x.h"
#include "lcd.h"
#include "LED.h"
#include "KEY.h"                                            
#include "ADC.h"
#include "PWMOC.h"
#include "UI.h"
#include "Stdio.h"
#include "String.h"

extern u8 Str[];

u8 Mode = 1;//AUTO:1,MANU:0
u8 UIIndex = 0;//Data:0,Para:1
//Para
u8 PA6Para = 10;//Duty
u8 PA7Para = 10;//Duty
//Flag


void FlagScan()
{
	//LED Setting
	if((Mode==1)&&(UIIndex==0))	  //00
	{
		LEDSetting(0xFC00);
	}
	else if((Mode==1)&&(UIIndex==1))  //10
	{
		LEDSetting(0xFE00);
	}
	else if((Mode==0)&&(UIIndex==0))  //01
	{
		LEDSetting(0xFD00);
	}
	else if((Mode==0)&&(UIIndex==1))  //11
	{
		LEDSetting(0xFF00);
	}
}

void DataUpdata()
{
	AD_Get();
	PWMConfig();	
}

void UI_Data()
{
	DataUpdata();
	FlagScan();
	sprintf((char *)Str,"       Data               ");
	LCD_DisplayStringLine(Line1 ,Str);
	sprintf((char *)Str,"     V:%.2fV             ", AD_Data);
	LCD_DisplayStringLine(Line3 ,Str);
	if(Mode)
	{
		sprintf((char *)Str,"     Mode:AUTO           ");
		LCD_DisplayStringLine(Line5 ,Str);
	}
	else 
	{
		sprintf((char *)Str,"     Mode:MANU           ");
		LCD_DisplayStringLine(Line5 ,Str);
	}
	
}

void UI_Para()
{
	DataUpdata();
	FlagScan();
	sprintf((char *)Str,"       Para               ");
	LCD_DisplayStringLine(Line1 ,Str);
	sprintf((char *)Str,"     PA6:%d%%               ", PA6Para);
	LCD_DisplayStringLine(Line3 ,Str);
	sprintf((char *)Str,"     PA7:%d%%               ", PA7Para);
	LCD_DisplayStringLine(Line5 ,Str);
}

void UISelect()
{
	static u8 UIIndex_BP = 0;
	if(UIIndex_BP != UIIndex)//Ë¢ÐÂÆÁÄ»
	{
		LCD_Clear(Black);
		UIIndex_BP = UIIndex;
	}
	if(!UIIndex)
	{
		UI_Data();
	}
	else
	{
		UI_Para();
	}
}
