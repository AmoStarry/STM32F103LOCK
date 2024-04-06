#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "LED.h"
#include "esp8266.h"
#include <Serial.h>
#include <Delay.h>
#include "OLED.h"

uint8_t RxData;			//�������ڽ��մ������ݵı���

int main(void)
{
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
     Timer_Init(10000,7200);   
     LED_Init();
     OLED_Init();
     USART1_Init();
     esp8266_init();
     
     /*��ʾ��̬�ַ���*/
	OLED_ShowString(1, 1, "RxData:");
	while(1)
	{
          
//          if (Serial_GetRxFlag() == 1)			//��鴮�ڽ������ݵı�־λ
//		{
//			RxData = Serial_GetRxData();		//��ȡ���ڽ��յ�����
//			Serial_SendByte(RxData);			//���ڽ��յ������ݻش���ȥ�����ڲ���
//			OLED_ShowHexNum(1, 8, RxData, 2);	//��ʾ���ڽ��յ�����
//		}
//    printf("AT+MQTTPUB=0,\"/sys/k0ygtxfPbcQ/esp8266/thing/event/property/post\",\"{\\\"params\\\":{\\\"temp\\\":88\\,\\\"humi\\\":88\\,\\\"led\\\":1}\\,\\\"version\\\":\\\"1.0.0\\\"}\",1,0\r\n");
//     Delay_ms(5000);
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

