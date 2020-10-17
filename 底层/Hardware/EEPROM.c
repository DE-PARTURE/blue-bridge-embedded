#include "i2c.h"
#include "EEPROM.h"

void EEWrite(u8 Addr,u8 Val)
{
	I2CStart();
	I2CSendByte(0xA0);//写器件地址
	I2CWaitAck();
	I2CSendByte(Addr);//写内存地址
	I2CWaitAck();
	I2CSendByte(Val);//发送数据
	I2CWaitAck();
	I2CStop();
}


u8 EERead(u8 Addr)
{
	u8 Dat;
	
	I2CStart();
	I2CSendByte(0xA0);//写器件地址
	I2CWaitAck();
	I2CSendByte(Addr);//写内存地址
	I2CWaitAck();
	
	I2CStart();//重新启动
	I2CSendByte(0xA1);//发送读指令
	I2CWaitAck();
	Dat = I2CReceiveByte();//读取数据
	I2CSendNotAck();//发送非应答
	I2CStop();
	
	return Dat;
}
