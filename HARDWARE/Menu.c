#include "Menu.h"
#include "Key.h"
#include "u8g2.h"
#include "picture.h"
#include <stdio.h>
#include "Delay.h"
extern u8g2_t u8g2;

uint8_t i = 0;
void Show_Menu_Config(void)
{
	u8g2_SetFontMode(&u8g2, 1);//��������ģʽ��mode����ģʽ�����ã�1������ã�0��͸��ģʽ
	u8g2_SetFontDirection(&u8g2, 0);//�������巽�� 
	u8g2_SetFont(&u8g2, u8g2_font_spleen6x12_mf);//���������ʽ
     
}

////����1���ƶ�����ʼλ�ã��󶨵�Ϊ��׼�� ����2������1�� -1�ң� ����3���ƶ���Χ
//void animateDisplay(int8_t initialDisplay, int8_t direction, int8_t maxDisplay) {
//    int8_t display = initialDisplay;
//    while ((direction > 0 && display < maxDisplay) || (direction < 0 && display > -maxDisplay)) {
//        u8g2_ClearBuffer(&u8g2); // �����ʾ����
//        u8g2_DrawXBM(&u8g2, 0 + direction * display, 16, 32, 32, password);
//        u8g2_DrawBox(&u8g2, 32 + direction * display, 0, 64, 64);
//        u8g2_DrawXBM(&u8g2, 32 + direction * display, 0, 64, 64, Image[i]);
//        u8g2_DrawXBM(&u8g2, 96 + direction * display, 16, 32, 32, setting);
//        u8g2_SendBuffer(&u8g2); // ��Ҫ��ʾ����Ϣд�뻺��
//        display += 3;           // ����λ��
//    }
//}	


void Show_Menu(Speed_ENUM Speed_choose)        // ��ʾ�˵�����������Ϊ��̬��ʾ�ٶȵ�ö������
{
     
    uint8_t index = 1; // ��ǰ�˵���������0��ʼ 
    uint8_t display =0;
    uint8_t key;

    while (1) 
    {
        key = Key_GetNum(); // ��ȡ����
                      
        if (key == 1)       // ��鰴�������ݰ�����������
        {   
            display =0;
            index = (index == 0) ? 1 : index - 1;
        } 
        else if (key == 2) 
        {
            display =0;
            index = (index == 2) ? 1 : index + 1;
        }    
         
        switch(index)
        {
             case 0:
               for(;display <32;display+=3)
               {
                    u8g2_ClearBuffer(&u8g2);                        // �����ʾ����
                    u8g2_DrawXBM(&u8g2, 0+display,16,32,32,password); 
                    u8g2_DrawBox(&u8g2,32+display, 0, 64, 64);
                    u8g2_DrawXBM(&u8g2,32+display, 0, 64, 64, Image[i]);
                    u8g2_DrawXBM(&u8g2,96+display,16,32,32,setting);
                    u8g2_SendBuffer(&u8g2);                         //��Ҫ��ʾ����Ϣд�뻺��                    
               };
               u8g2_ClearBuffer(&u8g2);                        // �����ʾ����
               u8g2_DrawXBM(&u8g2,32,0,64,64,password_big);    //��������ͼ��ͼƬ
               u8g2_SendBuffer(&u8g2);                         //��Ҫ��ʾ����Ϣд�뻺��
               break;
          case 1:
               u8g2_DrawXBM(&u8g2,0,16,32,32,password);        //��������ͼ��ͼƬ
               u8g2_DrawXBM(&u8g2,96,16,32,32,setting);        //��������ͼ��ͼƬ
               u8g2_SendBuffer(&u8g2);                         //��Ҫ��ʾ����Ϣд�뻺��
               i = (i + 1) % 14;
               u8g2_DrawBox(&u8g2, 32, 0, 64, 64);
               u8g2_DrawXBM(&u8g2, 32, 0, 64, 64, Image[i]);
               u8g2_SendBuffer(&u8g2);                         //��Ҫ��ʾ����Ϣд�뻺��
               u8g2_SetDrawColor(&u8g2, 1);
               Delay_ms(10); // ��ʱ10ms          
               break;
          case 2:
               for(;display <32;display+=3)
               {
                    u8g2_ClearBuffer(&u8g2);                        // �����ʾ����
                    u8g2_DrawXBM(&u8g2, 0-display,16,32,32,password);
                    u8g2_DrawBox(&u8g2,32-display, 0, 64, 64);
                    u8g2_DrawXBM(&u8g2,32-display, 0, 64, 64, Image[i]);
                    u8g2_DrawXBM(&u8g2,96-display,16,32,32,setting);
                    u8g2_SendBuffer(&u8g2);                         //��Ҫ��ʾ����Ϣд�뻺��
               }
               u8g2_ClearBuffer(&u8g2);                        // �����ʾ����
               u8g2_DrawXBM(&u8g2,32,0,64,64,setup);           //��������ͼ��ͼƬ
               u8g2_SendBuffer(&u8g2);                         //��Ҫ��ʾ����Ϣд�뻺��
               break;
        }
     }           
}


