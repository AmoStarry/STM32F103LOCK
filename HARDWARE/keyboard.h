#ifndef __KEY_BOARD_H__
#define __KEY_BOARD_H__
#include "stm32f10x.h"                  // Device header

// 定义行和列的GPIO引脚
#define KEYPAD_ROW_GPIO GPIOB
#define KEYPAD_ROW_PIN0 GPIO_Pin_0
#define KEYPAD_ROW_PIN1 GPIO_Pin_1
#define KEYPAD_ROW_PIN2 GPIO_Pin_2
#define KEYPAD_ROW_PIN3 GPIO_Pin_3  // 添加第四个行引脚

#define KEYPAD_COL_GPIO GPIOB
#define KEYPAD_COL_PIN0 GPIO_Pin_10
#define KEYPAD_COL_PIN1 GPIO_Pin_11
#define KEYPAD_COL_PIN2 GPIO_Pin_12

void key_board_init(void);
char get_key_board(void);
	
#endif
