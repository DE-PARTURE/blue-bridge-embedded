#include "Headfile.h"

u8 LIS302DL_X = 0;
u8 LIS302DL_Y = 0;
u8 LIS302DL_Z = 0;


void LIS302DL_Write(u8 Addr,u8 Val)
{
	I2CStart();
	I2CSendByte(0x38);//器件地址+写
	I2CWaitAck();
	I2CSendByte(Addr);//寄存器地址
	I2CWaitAck();
	I2CSendByte(Val);
	I2CWaitAck();
	I2CStop();
}

u8 LIS302DL_Read(u8 Addr)
{
	u8 Dat = 0;
	I2CStart();
	I2CSendByte(0x38);//器件地址+写
	I2CWaitAck();
	I2CSendByte(Addr);
	I2CWaitAck();

	I2CStart();
	I2CSendByte(0x39);//器件地址+读
	I2CWaitAck();
	Dat = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();

	return Dat;
}


void LIS302DL_Init()
{
	LIS302DL_Write(0x20,0x47);//使工作在正常模式，x、y、z寄存器输出使能
}

void LIS302DL_DataRead()
{
	LIS302DL_X = LIS302DL_Read(0x29);
	LIS302DL_Y = LIS302DL_Read(0x2B);
	LIS302DL_Z = LIS302DL_Read(0x2D);

}



