#include "stm32f10x.h"                  // Device header
#include "Timer.h"
/**
  * ��    ������ʱ�жϳ�ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void Timer_Init(u16 Psc,u16 Pre)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
     NVIC_InitTypeDef NVIC_InitStructure;						//����ṹ�����
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);			//����TIM1��ʱ��
	

	/*ʱ����Ԫ��ʼ��*/
     TIM_TimeBaseInitStructure.TIM_Prescaler =Psc-1;                 //Ԥ��Ƶ������PSC��ֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;     //������ģʽ��ѡ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = Pre-1;	                 //��װ��ֵ����ARR��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		  //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����			
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter =0;			  //�ظ����������߼���ʱ���Ż��õ�  
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
     
     TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);					//����TIM�ĸ����ж�
     

     
     /*NVIC����*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;			//ѡ������NVIC��TIM1��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	     //ָ��NVIC��·����ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ָ��NVIC��·ʹ��
	NVIC_Init(&NVIC_InitStructure);						     //���ṹ���������NVIC_Init������NVIC����
     
	TIM_Cmd(TIM1, ENABLE);	                                         //�ܿ���		
}
