#ifndef IIC_H_
#define IIC_H_

void IICInit(void);
void delay1(unsigned int n);

void I2CStart(void);
void I2CStop(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
unsigned char I2CWaitAck(void);

void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);

//For EEPROM
void EEWrite(u8 Addr,u8 Dat);
u8	 EERead(u8 Addr);

#endif
