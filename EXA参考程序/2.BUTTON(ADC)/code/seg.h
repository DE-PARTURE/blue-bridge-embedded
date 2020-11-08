#ifndef __SEG_H
#define __SEG_H

#define RCLK_H			GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RCLK_L			GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define SER_H			GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define SER_L			GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define SCK_H			GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define SCK_L			GPIO_ResetBits(GPIOA,GPIO_Pin_3)

void STM3210B_SEG_Init(void);
void SEG_DisplayValue(u8 Bit1,u8 Bit2,u8 Bit3);

#endif
