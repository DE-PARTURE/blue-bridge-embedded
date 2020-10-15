#include "stm32f10x.h"
#include "I2C.h"


void EEWrite(u8 Addr,u8 Dat)
{
	I2CStart();
	I2CSendByte(0xA0);
	I2CWaitAck();
	I2CSendByte(Addr);//ÄÚ´æµØÖ·
	I2CWaitAck();
	I2CSendByte(Dat);
	I2CWaitAck();
	I2CStop();

}

u8 EERead(u8 Addr)
{
	u8 Dat = 0;
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


