#include "keyboard.h"
#include "Delay.h"

#define sdo(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)(x))
#define scl(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction)(x))
#define re_sdo      GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
void Tttp229_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//设置为下拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
}

uint8_t Key_board(void)
{
	unsigned char i;
	unsigned int temp = 0;
     uint8_t KEY;
	sdo(0);
	Delay_us(100);
	sdo(1);
	Delay_us(10);	
	for(i=0;i<16;i++)
	{
	temp>>=1;
		scl(0);
		if( re_sdo != 0)
			temp|=0x8000;
		scl(1);
	}
     if(temp ==0x0001) {KEY ='1';}
     else if(temp ==0x0002) {KEY ='2';}
     else if(temp ==0x0004) {KEY ='3';}
     else if(temp ==0x0008) {KEY ='4';}
     else if(temp ==0x0010) {KEY ='5';}
     else if(temp ==0x0020) {KEY ='6';}
     else if(temp ==0x0040) {KEY ='7';}
     else if(temp ==0x0080) {KEY ='8';}
     else if(temp ==0x0100) {KEY ='9';}
     else if(temp ==0x0200) {KEY ='0';}
     else if(temp ==0x0400) {KEY ='*';}
     else if(temp ==0x0800) {KEY ='#';}
     else if(temp ==0x1000) {KEY ='A';}
     else if(temp ==0x2000) {KEY ='B';}
     else if(temp ==0x4000) {KEY ='C';}
     
return KEY;
}


