#include "stm32f10x.h"
#include "i2c.h"
#include "mems.h"
#include "main.h"

u8 alz[3] ;

//
void LIS302DL_Write(unsigned char reg,unsigned char info)
{	
	I2CStart(); 
	I2CSendByte(0x38);  
	I2CWaitAck();     
	I2CSendByte(reg);  
	I2CWaitAck(); 
	I2CSendByte(info); 
	I2CWaitAck();
	I2CStop();
}

//
uint8_t LIS302DL_Read(uint8_t address)
{
	unsigned char val;
	I2CStart(); 
	I2CSendByte(0x38);  
	I2CWaitAck();     
	
	I2CSendByte(address);  
	I2CWaitAck(); 
	
	I2CStart();
	I2CSendByte(0x39); 
	I2CWaitAck();
	val = I2CReceiveByte(); 
	I2CSendNotAck();
	I2CStop();
	
	return(val);
}

//
u8* Lis302DL_Output(void)
{
	if((LIS302DL_Read(0x27) & 0x08) != 0){
		
		alz[0] = (LIS302DL_Read(0x29));  //x
		alz[1] = (LIS302DL_Read(0x2B));  //y
		alz[2] = (LIS302DL_Read(0x2D));  //z
	}

	return alz;
}

//
void LIS302DL_Config(void)
{
	LIS302DL_Write(CTRL_REG1,0x47);
	LIS302DL_Write(CTRL_REG2,0x00);
	LIS302DL_Write(CTRL_REG3,0xC1);
	LIS302DL_Write(FF_WU_THS_1,0x28);		
	LIS302DL_Write(FF_WU_DURATION_1,40);		
	LIS302DL_Write(FF_WU_CFG_1,0x10);		
}

//
uint8_t LIS302DL_Check(void)
{
	if(LIS302DL_Read(0x0f)){
		return 1;
	}else{
		return 0;
	}
}

