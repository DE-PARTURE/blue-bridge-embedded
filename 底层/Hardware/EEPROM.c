#include "i2c.h"
#include "EEPROM.h"

void EEWrite(u8 Addr,u8 Val)
{
	I2CStart();
	I2CSendByte(0xA0);
	I2CWaitAck();
	I2CSendByte(Addr);
	I2CWaitAck();
	I2CSendByte(Val);
	I2CWaitAck();
	I2CStop();
}


u8 EERead(u8 Addr)
{
	u8 Dat;
	
	I2CStart();
	I2CSendByte(0xA0);
	I2CWaitAck();
	I2CSendByte(Addr);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(0xA1);
	I2CWaitAck();
	Dat = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
	return Dat;
}
