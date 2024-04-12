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
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_hw_i2c,u8g2_gpio_and_delay_stm32);//U8G2_R0������Ļ����
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
//     FPM383C_Init();	//ָ��ģ���ʼ������     
//     esp8266_send_data();
     Key_Init();//������ʼ��
	I2C_Config();//I2C����GPIO�ڳ�ʼ��
	u8g2_Config();//u8g2���ʼ��
     Show_Menu_Config(); //�˵���ʼ��
     
	while(1)
	{
           Show_Menu(fast_speed);  //�˵��춯�������޸�"fast_speed"���Ը����ƹ����ٶ�
//          FPM383C_Loop();
//          esp8266_receive_data();
	}
}

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)  //�ж��Ƿ���TIM1�ĸ����¼��������ж�
	{
          
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIM1�����¼����жϱ�־λ      
          LED0_Toggle();	 //ÿһ�������תһ�µ�ƽ																									//�����жϽ��������ϵش�����������������
	}
}

