#include "Menu.h"
#include "Key.h"
#include "u8g2.h"
#include "picture.h"
#include <stdio.h>
#include "Delay.h"

Speed_ENUM Speed_choose;

extern u8g2_t u8g2;
int16_t display=32;
int16_t diaplay_trg=1;
uint8_t circle_num;
uint8_t KeyNum;
static uint8_t Picture_Flag=0;//����ѡ���־λ
const char words[][10] = {{"GAME\0"},{"MESSAGE\0"},{"SETTING\0"}};
uint8_t Game_Menu_Flag=0;

void ui_run(char* a ,char* a_trg,int b)
{
	if(*a < *a_trg)
	{
		*a+=b;
		if(*a > *a_trg)	//��ֹ�ӹ�ͷ
			*a = *a_trg;
	}
	if(*a > *a_trg)
	{
		*a-=b;
		if(*a < *a_trg)//��ֹ����ͷ
			*a = *a_trg;
	}
}

void ui_right_one_Picture(int16_t* a, int b)
{
	uint8_t i=0;
	if((i<=32))
	{
		*a+=b;
		i+=b;
	}
}

void ui_left_one_Picture(int16_t* a, int b )
{
	uint8_t i=0;
	if((i<=32))
	{
		*a-=b;
		i+=b; 
	}
}

void Show_Menu_Config(void)
{
	u8g2_SetFontMode(&u8g2, 1);//��������ģʽ��mode����ģʽ�����ã�1������ã�0��͸��ģʽ
	u8g2_SetFontDirection(&u8g2, 0);//�������巽�� 
	u8g2_SetFont(&u8g2, u8g2_font_spleen6x12_mf);//���������ʽ
     
	u8g2_DrawXBM(&u8g2,0,16,32,32,password);        //������Ϣͼ��ͼƬ
	u8g2_DrawXBM(&u8g2,display+64,16,32,32,setting);//��������ͼ��ͼƬ  
	u8g2_SendBuffer(&u8g2);                         //��Ҫ��ʾ����Ϣд�뻺��
}

void u8g2_Show_Astronaut(u8g2_t *u8g2, unsigned char i)
{
	u8g2_SetDrawColor(u8g2, 0);
	u8g2_DrawBox(u8g2, display, 0, 64, 64);
	u8g2_DrawXBM(u8g2, display, 0, 64, 64, Image[i]);
	u8g2_SendBuffer(u8g2);
	
}

void Show_Menu(Speed_ENUM Speed_choose)        // ��ʾ�˵�����������Ϊ��̬��ʾ�ٶȵ�ö������
{
     uint8_t i = 0;
    	while(1)
	{
          KeyNum = Key_GetNum();                     // ��ȡ�������
		u8g2_Show_Astronaut(&u8g2, i);
		i++;
		if(i>=14)
		{
			i = 0;
		}
		Delay_ms(10);
          if(KeyNum ==1||KeyNum ==2||KeyNum ==3) break;
	}
     

     Game_Menu_Flag = KeyNum;                   // ��������Ÿ�ֵ����Ϸ�˵���־λ
    
    if ((KeyNum == 1) && (display > -32))      // ��������˰���1������ʾλ�ô���-48
    {
        Picture_Flag++;                        // ͼƬ��־λ�����������л���ʾ"GAME","MESSAGE","SETTING"
        circle_num = 32 / Speed_choose;        // �����ٶ�ѡ������ѭ���������ٶ�Խ������Խ˿��
        
        while (circle_num)                     // ��ѭ��������Ϊ0ʱ
        {
            u8g2_ClearBuffer(&u8g2);           // �����ʾ����
            display = display-Speed_choose;     
            u8g2_SetDrawColor(&u8g2, 1); 
//            u8g2_DrawBox(&u8g2, display, 0, 64, 64);
//	       u8g2_DrawXBM(&u8g2, display, 0, 64, 64, Image[i]); 
            u8g2_DrawXBM(&u8g2, display + 64, 0, 64,64, setup);
            u8g2_SendBuffer(&u8g2); // ����������ݷ��͵���ʾ�豸
            
            circle_num--; // ѭ�������ݼ�
        }
        
        KeyNum = 0; // ���ð������
    }
    else if ((KeyNum == 2) && (display < 32))  // ��������˰���2������ʾλ��С��48
    {
        Picture_Flag--;                       // ͼƬ��־λ�Լ��������л���ʾ"GAME","MESSAGE","SETTING"
        
        circle_num = 32 / Speed_choose;       // �����ٶ�ѡ������ѭ������
        while (circle_num)                    // ͬ�ϣ������ƶ�ͼƬ
        {
            u8g2_ClearBuffer(&u8g2);
            ui_right_one_Picture(&display, Speed_choose);

            u8g2_SetDrawColor(&u8g2, 1); 
//            u8g2_DrawBox(&u8g2, display, 0, 64, 64);
//	       u8g2_DrawXBM(&u8g2, display, 0, 64, 64, Image[i]); 
            u8g2_DrawXBM(&u8g2, display + 96, 0, 64, 64, setup);
            u8g2_SendBuffer(&u8g2);
            circle_num--;
        }
        KeyNum = 0;   // ���ð������
    }
    else ;           // ���û�а��������£���ִ���κβ���
    
                     // ����ͼƬ��־λ��ֵ����ʾ��ͬ�Ĳ˵���
//    switch (Picture_Flag)
//    {
//        case 0:
//            // ��ʾ"GAME"�˵���
//            u8g2_DrawStr(&u8g2, 52, 10, "MENU:");
//            u8g2_DrawStr(&u8g2, 82, 10, &words[0][0]); // ��ʾ"���ܲ˵�"�������˵��
//            u8g2_SendBuffer(&u8g2);
//            Game_Menu(); // ������Ϸ�˵�����
//            break;
//        
//        case 1:
//            // ��ʾ"MESSAGE"�˵���
//            u8g2_DrawStr(&u8g2, 52, 10, "MENU:");
//            u8g2_DrawStr(&u8g2, 82, 10, &words[1][0]); // ��ʾ"��Ϣ�˵�"�������˵��
//            u8g2_SendBuffer(&u8g2);
//            break;
//        
//        case 2:
//            // ��ʾ"SETTING"�˵���
//            u8g2_DrawStr(&u8g2, 52, 10, "MENU:");
//            u8g2_DrawStr(&u8g2, 82, 10, &words[2][0]); // ��ʾ"���ò˵�"�������˵��
//            u8g2_SendBuffer(&u8g2);
//            break;
//    }
}


void Game_Menu(void) 
{
	static char Box_x = 1;//����С������ֲ�����ʼֵ
	static char Box_y = 14;
	static char Box_w = 84;
	static char Box_h = 13;
	       
	static char Box_x_trg;//����С����Ŀ��ֵ
	static char Box_y_trg;
	static char Box_w_trg;
	static char Box_h_trg;
	
	static int8_t Box_Flag = 0;
	
	if(Game_Menu_Flag == 3)//ȷ�ϼ�
	{
		To_Game_Menu_Display();
		while(1)
		{	
			Game_Menu_Flag = Key_GetNum(); 
			u8g2_ClearBuffer(&u8g2);
			
			u8g2_DrawStr(&u8g2,52,10,"GAME");
			u8g2_DrawLine(&u8g2, 1, 13, 128, 13);
			u8g2_DrawStr(&u8g2,3,24,"game1:FlyBird");
			u8g2_DrawStr(&u8g2,3,36,"game2:Dinosaur Rex");
			u8g2_DrawStr(&u8g2,3,48,"game3:Stick Fight");
			u8g2_DrawStr(&u8g2,3,60,"game4:Tetris");
			
			ui_run(&Box_x, &Box_x_trg,1);
			ui_run(&Box_y, &Box_y_trg,1);
			ui_run(&Box_w, &Box_w_trg,2);
			ui_run(&Box_h, &Box_h_trg,1);
			
			u8g2_DrawFrame(&u8g2, Box_x, Box_y, Box_w, Box_h);
			u8g2_SendBuffer(&u8g2);
			
			if(Game_Menu_Flag == 1)
			{
				Box_Flag++;
				if(Box_Flag >= 3)Box_Flag=3;
			}
			
			if(Game_Menu_Flag == 2)
			{
				Box_Flag--;
				if(Box_Flag <= 0)Box_Flag=0;
			}
	
			if(Game_Menu_Flag == 4)
			{
				u8g2_ClearBuffer(&u8g2);
				Game_To_Menu_Display();  
				break;
			}
			
			switch(Box_Flag)//��ȡ�������Ŀ��ֵ
			{
				case 0: Box_x_trg = 1;Box_y_trg = 14;Box_w_trg = sizeof("game1:FlyBird")*6;Box_h_trg = 13;break;
				case 1: Box_x_trg = 1;Box_y_trg = 27;Box_w_trg = sizeof("game2:Dinosaur Rex")*6;Box_h_trg = 13;break;
				case 2: Box_x_trg = 1;Box_y_trg = 38;Box_w_trg = sizeof("game1:Stick Fight")*6;Box_h_trg = 13;break;
				case 3: Box_x_trg = 1;Box_y_trg = 51;Box_w_trg = sizeof("game1:Tetris")*6;Box_h_trg = 12;break;
			}                              
		}               
	}  
	Game_Menu_Flag = 0;//����	
	Show_Menu_Config();//�ص�����ʾҳ��
	display = 48;
	Picture_Flag = 0;
}
void To_Game_Menu_Display(void)//�˵�����Ϸ�˵����ɶ���
{
	char Game_Menu_Display = 10;
	char Game_Menu_Display_trg =74;
	
	while(Game_Menu_Display != Game_Menu_Display_trg)
	{	
		
//		u8g2_ClearBuffer(&u8g2);
//		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"MENU:");//YҪ��Ϊ0��72��MENU���Ż���ȫ��ʧ
//		u8g2_DrawXBM(&u8g2,44,Game_Menu_Display+26,40,40,arrowhead);//�����ͷ��־ͼƬ
//		u8g2_DrawXBM(&u8g2,display,Game_Menu_Display+6,32,32,game);//������Ϸͼ��ͼƬ
//		u8g2_DrawXBM(&u8g2,display+48,Game_Menu_Display+6,32,32,wechat);//������Ϣͼ��ͼƬ
//		u8g2_DrawXBM(&u8g2,display+96,Game_Menu_Display+6,32,32,setting);//��������ͼ��ͼƬ  
//		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
//		u8g2_SendBuffer(&u8g2);//��Ҫ��ʾ����Ϣд�뻺��
	}
	
		Game_Menu_Display = 74;	
		Game_Menu_Display_trg =10;

	while(Game_Menu_Display != Game_Menu_Display_trg)
	{	u8g2_ClearBuffer(&u8g2);
		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"GAME");//Game_Menu_Display+16+62Ϊ72����ʱ��Game����ʧ
		u8g2_DrawLine(&u8g2, 1, Game_Menu_Display+3, 128, Game_Menu_Display+3);
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+14,"game1:FlyBird");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+26,"game2:Dinosaur Rex");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+38,"game3:Stick Fight");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+50,"game4:Tetris");
		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
		u8g2_SendBuffer(&u8g2);//��Ҫ��ʾ����Ϣд�뻺��
	}	
}

void Game_To_Menu_Display(void)//��Ϸ�˵����˵����ɶ���
{
	char Game_Menu_Display = 10;
	char Game_Menu_Display_trg =74;
	
	while(Game_Menu_Display != Game_Menu_Display_trg)
	{	
		u8g2_ClearBuffer(&u8g2);
		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"GAME");//Game_Menu_Display+16+62Ϊ72����ʱ��Game����ʧ
		u8g2_DrawLine(&u8g2, 1, Game_Menu_Display+3, 128, Game_Menu_Display+3);
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+14,"game1:FlyBird");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+26,"game2:Dinosaur Rex");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+38,"game3:Stick Fight");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+50,"game4:Tetris");
		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
		u8g2_SendBuffer(&u8g2);//��Ҫ��ʾ����Ϣд�뻺��
	}
		Game_Menu_Display = 74;	
		Game_Menu_Display_trg =10;

//	while(Game_Menu_Display != Game_Menu_Display_trg)
//	{	
//		u8g2_ClearBuffer(&u8g2);
//		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
//		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"MENU:");//YҪ��Ϊ0��>=72��MENU���Ż���ȫ��ʧ
//		u8g2_DrawXBM(&u8g2,44,Game_Menu_Display+26,40,40,arrowhead);//�����ͷ��־ͼƬ
//		u8g2_DrawXBM(&u8g2,display,Game_Menu_Display+6,32,32,game);//������Ϸͼ��ͼƬ
//		u8g2_DrawXBM(&u8g2,display+48,Game_Menu_Display+6,32,32,wechat);//������Ϣͼ��ͼƬ
//		u8g2_DrawXBM(&u8g2,display+96,Game_Menu_Display+6,32,32,setting);//��������ͼ��ͼƬ  
//		u8g2_SendBuffer(&u8g2);//��Ҫ��ʾ����Ϣд�뻺��
//	}	
}

