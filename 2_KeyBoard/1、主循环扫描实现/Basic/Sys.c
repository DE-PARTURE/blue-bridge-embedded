#include "HeadFile.h"

Task Action1;
Task Action2;
Task Action3;
Task Action4;

void TaskInit(Task *task){
	task -> StartFlag = 0;
	task -> ExcuteFlag = 0;
	task -> EndFlag = 0;
}

void StartFlagScan(void){
	if(Action1.StartFlag){
		Action1.StartFlag = 0;
		Action1.ExcuteFlag = 1;
		LCD_DisplayStringLine(1,"Mode 1");
	}else if(Action2.StartFlag){
		Action2.StartFlag = 0;
		Action2.ExcuteFlag = 1;	
		LCD_DisplayStringLine(1,"Mode 2");
	}else if(Action3.StartFlag){
		Action3.StartFlag = 0;
		Action3.ExcuteFlag = 1;
		LCD_DisplayStringLine(1,"Mode 3");
	}else if(Action4.StartFlag){
		Action4.StartFlag = 0;
		Action4.ExcuteFlag = 1;
		LCD_DisplayStringLine(1,"Mode 4");
	}
	
}

void ExcuteFlagScan(void){
	//不可同步执行用else if
	if(Action1.ExcuteFlag){
		Delay_Ms(100);
	}else if(Action2.ExcuteFlag){
		Delay_Ms(100);
	}else if(Action3.ExcuteFlag){
		Delay_Ms(100);
	}else if(Action4.ExcuteFlag){
		Delay_Ms(100);
	}
}

void EndFlagScan(void){
	if(Action1.EndFlag){
		Action1.EndFlag = 0;
		Action1.ExcuteFlag = 0;
		LCD_Clear(Blue2);
		LEDReset();
	}else if(Action2.EndFlag){
		Action2.EndFlag = 0;
		Action2.ExcuteFlag = 0;
		LCD_Clear(Blue2);
		LEDReset();
	}else if(Action3.EndFlag){
		Action3.EndFlag = 0;
		Action3.ExcuteFlag = 0;
		LCD_Clear(Blue2);
		LEDReset();
	}else if(Action4.EndFlag){
		Action4.EndFlag = 0;
		Action4.ExcuteFlag = 0;
		LCD_Clear(Blue2);
		LEDReset();
	}
}
