#include "stm32f10x.h"                  // Device header
#include "LED.h"

#define LED_GPIO GPIOA
#define LED_PIN0 GPIO_Pin_9
#define LED_PIN1 GPIO_Pin_10

void LED_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启LED_GPIO的时钟
	
	/*GPIO初始化*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_PIN0 | LED_PIN1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_ResetBits(LED_GPIO, LED_PIN0 | LED_PIN1);				//设置PA0和PA1引脚为低电平
}


void LED0_Toggle(void)
{
	if (GPIO_ReadOutputDataBit(LED_GPIO, LED_PIN0) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(LED_GPIO, LED_PIN0);					//则设置PA0引脚为高电平
	}
	else												//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(LED_GPIO, LED_PIN0);					//则设置PA0引脚为低电平
	}
}

void LED1_Toggle(void)
{
	if (GPIO_ReadOutputDataBit(LED_GPIO, LED_PIN1) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(LED_GPIO, LED_PIN1);					//则设置PA1引脚为高电平
	}
	else												//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(LED_GPIO, LED_PIN1);					//则设置PA1引脚为低电平
	}
}
