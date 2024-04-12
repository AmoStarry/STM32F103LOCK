#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "LED.h"
#include "esp8266.h"
#include <Serial.h>
#include <Delay.h>
#include "OLED.h"
#include "FPM383C.h"
#include "keyboard.h"

#include "u8g2.h"
#include "Key.h"
#include "Menu.h"

uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr);
u8g2_t u8g2;

void u8g2_Config()
{
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_hw_i2c,u8g2_gpio_and_delay_stm32);//U8G2_R0代表屏幕方向
	u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
	u8g2_SetPowerSave(&u8g2, 0); // wake up display
	u8g2_ClearBuffer(&u8g2);
}


int main(void)
{
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
     Timer_Init(10000,7200);   
     LED_Init();
     OLED_Init();
     USART1_Init();
//     esp8266_init();
//     FPM383C_Init();	//指纹模块初始化函数     
//     esp8266_send_data();
     Key_Init();//按键初始化
	I2C_Config();//I2C所用GPIO口初始化
	u8g2_Config();//u8g2库初始化
     Show_Menu_Config(); //菜单初始化
     
	while(1)
	{
           Show_Menu(fast_speed);  //菜单混动函数，修改"fast_speed"可以更改移滚动速度
//          FPM383C_Loop();
//          esp8266_receive_data();
	}
}

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)  //判断是否是TIM1的更新事件触发的中断
	{
          
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除TIM1更新事件的中断标志位      
          LED0_Toggle();	 //每一秒进来翻转一下电平																									//否则中断将连续不断地触发，导致主程序卡死
	}
}

