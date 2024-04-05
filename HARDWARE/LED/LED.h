#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"                  // Device header

#define LED0(X) GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)X)
#define LED1(X) GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)X)

void LED_Init(void);
void LED0_Toggle(void);
void LED1_Toggle(void);
#endif
