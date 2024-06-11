#include "stm32f10x.h"                  // Device header
#include "LED.h"

#define LED_GPIO GPIOA
#define LED_PIN0 GPIO_Pin_9
#define LED_PIN1 GPIO_Pin_10

void LED_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//����LED_GPIO��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_PIN0 | LED_PIN1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);						//��PA1��PA2���ų�ʼ��Ϊ�������
	
	/*����GPIO��ʼ�����Ĭ�ϵ�ƽ*/
	GPIO_ResetBits(LED_GPIO, LED_PIN0 | LED_PIN1);				//����PA0��PA1����Ϊ�͵�ƽ
}


void LED0_Toggle(void)
{
	if (GPIO_ReadOutputDataBit(LED_GPIO, LED_PIN0) == 0)		//��ȡ����Ĵ�����״̬�������ǰ��������͵�ƽ
	{
		GPIO_SetBits(LED_GPIO, LED_PIN0);					//������PA0����Ϊ�ߵ�ƽ
	}
	else												//���򣬼���ǰ��������ߵ�ƽ
	{
		GPIO_ResetBits(LED_GPIO, LED_PIN0);					//������PA0����Ϊ�͵�ƽ
	}
}

void LED1_Toggle(void)
{
	if (GPIO_ReadOutputDataBit(LED_GPIO, LED_PIN1) == 0)		//��ȡ����Ĵ�����״̬�������ǰ��������͵�ƽ
	{
		GPIO_SetBits(LED_GPIO, LED_PIN1);					//������PA1����Ϊ�ߵ�ƽ
	}
	else												//���򣬼���ǰ��������ߵ�ƽ
	{
		GPIO_ResetBits(LED_GPIO, LED_PIN1);					//������PA1����Ϊ�͵�ƽ
	}
}
