#include "stm32f10x.h"                  // Device header
#include "Timer.h"
/**
  * 函    数：定时中断初始化
  * 参    数：无
  * 返 回 值：无
  */
void Timer_Init(u16 Psc,u16 Pre)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
     NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);			//开启TIM1的时钟
	

	/*时基单元初始化*/
     TIM_TimeBaseInitStructure.TIM_Prescaler =Psc-1;                 //预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;     //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = Pre-1;	                 //重装载值，即ARR的值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		  //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能			
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter =0;			  //重复计数器，高级定时器才会用到  
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
     
     TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);					//开启TIM的更新中断
     

     
     /*NVIC配置*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;			//选择配置NVIC的TIM1线
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	     //指定NVIC线路的抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_Init(&NVIC_InitStructure);						     //将结构体变量交给NVIC_Init，配置NVIC外设
     
	TIM_Cmd(TIM1, ENABLE);	                                         //总开关		
}
