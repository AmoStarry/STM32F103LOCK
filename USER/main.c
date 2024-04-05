#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "LED.h"
#include "esp8266.h"
#include <Serial.h>
#include <Delay.h>
     
int main(void)
{
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
     Timer_Init(10000,7200);   
     LED_Init();
     
     Serial_Init();
     esp8266_init();
	while(1)
	{
     printf("AT+MQTTPUB=0,\"/sys/k0ygtxfPbcQ/esp8266/thing/event/property/post\",\"{\\\"params\\\":{\\\"temp\\\":88\\,\\\"humi\\\":88\\,\\\"led\\\":1}\\,\\\"version\\\":\\\"1.0.0\\\"}\",1,0\r\n");
     Delay_ms(5000);
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

