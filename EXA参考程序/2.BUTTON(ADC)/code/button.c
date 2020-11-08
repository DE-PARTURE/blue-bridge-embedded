#include "adc.h"
#include "stm32f10x.h"
#include "button.h"

static u16 btn_buff[BTN_BUFF_LEN];

//
u16 Read_Btn(void)//中值滤波算法
{
	u16 tmp;
	u8 i = 0,j = 0;
	
	for(i=0; i<BTN_BUFF_LEN; i++){
		btn_buff[i] = Read_ADC();//获取BTN_BUFF_LEN次ADC原始值
	}

	for(i=0; i<=BTN_BUFF_LEN - 1; i++){//冒泡排序
		for(j=0; j<	BTN_BUFF_LEN-i-1; j++){
			if(btn_buff[j+1] < btn_buff[j]){
				tmp = btn_buff[j+1];
				btn_buff[j+1] = btn_buff[j];
				btn_buff[j] = tmp;
			}
		}
	}

	if(BTN_BUFF_LEN % 2 == 0){//如果数据数量为偶数个取ADC数值缓冲区中中间两个数的平均值返回
		return(btn_buff[BTN_BUFF_LEN/2-1] + btn_buff[BTN_BUFF_LEN/2])/2;
	}else{//如果数据数量为奇数个取ADC数值缓冲区中中间值返回
		return(btn_buff[BTN_BUFF_LEN/2]);
	}
}

//
u8 Scan_Btn(void)
{
	u16 btn_tmp = 0;

	btn_tmp = Read_Btn();//Read_ADC();

	if(btn_tmp <= 0x0020){
		return 1;
	}else if((btn_tmp >= 0x00B0) && (btn_tmp <= 0x0100)){
		return 2;
	}else if((btn_tmp >= 0x0240) && (btn_tmp <= 0x0300)){
		return 3;
	}else if((btn_tmp >= 0x03B0) && (btn_tmp <= 0x0450)){
		return 4; 
	}else if((btn_tmp >= 0x0500) && (btn_tmp <= 0x0600)){
		return 5;
	}else if((btn_tmp >= 0x0700) && (btn_tmp <= 0x0800)){
		return 6;
	}else if((btn_tmp >= 0x0840) && (btn_tmp <= 0x0940)){
		return 7;
	}else if(btn_tmp <= 0x0B50){
		return 8;
	}else{
		return 0;	//error status & no key
	}
}
