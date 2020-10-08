#ifndef BUZZER_H_
#define BUZZER_H_

#define BuzzerReset 	GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define BuzzerSet 		GPIO_ResetBits(GPIOB,GPIO_Pin_4)


void BuzzerInit(void);


#endif
