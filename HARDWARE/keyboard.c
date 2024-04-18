#include "keyboard.h"
#include "Delay.h"



void key_board_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置行为输出
    GPIO_InitStructure.GPIO_Pin = KEYPAD_ROW_PIN0 | KEYPAD_ROW_PIN1 | KEYPAD_ROW_PIN2 |KEYPAD_ROW_PIN3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(KEYPAD_ROW_GPIO, &GPIO_InitStructure);

    // 配置列为输入
    GPIO_InitStructure.GPIO_Pin = KEYPAD_COL_PIN0 | KEYPAD_COL_PIN1 | KEYPAD_COL_PIN2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_Init(KEYPAD_COL_GPIO, &GPIO_InitStructure);
}

char get_key_board(void)
{
     uint16_t row_pins[4] = {KEYPAD_ROW_PIN0, KEYPAD_ROW_PIN1, KEYPAD_ROW_PIN2, KEYPAD_ROW_PIN3};
     uint16_t col_pins[3] = {KEYPAD_COL_PIN0, KEYPAD_COL_PIN1, KEYPAD_COL_PIN2};
     char key_map[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
     };
     char key = '\0';
     
     for (int row = 0; row < 4; ++row) 
     {         
          GPIO_ResetBits(KEYPAD_ROW_GPIO, row_pins[row]);                                   // 设置当前行为低电平 
          for (int col = 0; col < 3; ++col)                                                 // 检查列是否为低电平
          {                  
               if (GPIO_ReadInputDataBit(KEYPAD_COL_GPIO, col_pins[col]) == Bit_RESET) 
               {
                    Delay_ms(20);                                                           // 在确认按键按下前进行延时消抖
                    if (GPIO_ReadInputDataBit(KEYPAD_COL_GPIO, col_pins[col]) == Bit_RESET) // 再次检查确保按键确实被按下
                    {                  
                         key = key_map[row][col];                                           // 等待按键释放（简单的消抖）
                         while (GPIO_ReadInputDataBit(KEYPAD_COL_GPIO, col_pins[col]) == Bit_RESET);
                         Delay_ms(20);                                                      // 在确认按键释放后进行延时消抖
                         break;
                    }
               }
          }
          GPIO_SetBits(KEYPAD_ROW_GPIO, row_pins[row]);                                       // 设置当前行为高电平 
          if (key != '\0'){
            break;
          }
    }
    return key;
}

