#include "Headfile.h"

int main(void)
{
	u16 led0pwmval = 0;
	u8 dir = 1;
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LEDInit();
	//闪灯
	Delay_Ms(200);
	LEDCmd(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC) & 0x00FF);
	LEDCmd(Bit_RESET);
	Delay_Ms(200);
	LEDCmd(Bit_SET);
	GPIO_Write(GPIOC,GPIO_ReadOutputData(GPIOC) | 0xFF00);
	LEDCmd(Bit_RESET);
	//
	LEDCmd(Bit_SET);
	Timer3PWMInit(899,99);//72000000/900/1000=800Hz  ω=72MHz/arr/psc
	
//	STM3210B_LCD_Init();
//	LCD_Clear(Blue);
//	LCD_SetBackColor(Blue);
//	LCD_SetTextColor(White);
	
	
	while(1){
		
 		Delay_Ms(10);	 
		if(dir)led0pwmval++;
		else led0pwmval--;

 		if(led0pwmval>300)dir=0;
		if(led0pwmval==0)dir=1;	
		//(5)、修改 TIM3_CCR3、TIM3_CCR4 来控制占空比。		
		TIM_SetCompare3(TIM3,led0pwmval);				//LD1
		TIM_SetCompare4(TIM3,301-led0pwmval);		//LD2
	}	 
}


