#include "stm32f10x.h"                  // Device header
#include "LED.h"

void LED_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//����GPIOA��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//��PA1��PA2���ų�ʼ��Ϊ�������
	
	/*����GPIO��ʼ�����Ĭ�ϵ�ƽ*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);				//����PA0��PA1����Ϊ�͵�ƽ
}


void LED0_Toggle(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0)		//��ȡ����Ĵ�����״̬�������ǰ��������͵�ƽ
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);					//������PA0����Ϊ�ߵ�ƽ
	}
	else												//���򣬼���ǰ��������ߵ�ƽ
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);					//������PA0����Ϊ�͵�ƽ
	}
}

void LED1_Toggle(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)		//��ȡ����Ĵ�����״̬�������ǰ��������͵�ƽ
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);					//������PA1����Ϊ�ߵ�ƽ
	}
	else												//���򣬼���ǰ��������ߵ�ƽ
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);					//������PA1����Ϊ�͵�ƽ
	}
}
