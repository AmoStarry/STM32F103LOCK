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
static uint8_t Picture_Flag=0;//功能选择标志位
const char words[][10] = {{"GAME\0"},{"MESSAGE\0"},{"SETTING\0"}};
uint8_t Game_Menu_Flag=0;

void ui_run(char* a ,char* a_trg,int b)
{
	if(*a < *a_trg)
	{
		*a+=b;
		if(*a > *a_trg)	//防止加过头
			*a = *a_trg;
	}
	if(*a > *a_trg)
	{
		*a-=b;
		if(*a < *a_trg)//防止减过头
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
	u8g2_SetFontMode(&u8g2, 1);//设置字体模式，mode字体模式，启用（1）或禁用（0）透明模式
	u8g2_SetFontDirection(&u8g2, 0);//设置字体方向 
	u8g2_SetFont(&u8g2, u8g2_font_spleen6x12_mf);//设置字体格式
     
	u8g2_DrawXBM(&u8g2,0,16,32,32,password);        //传入信息图标图片
	u8g2_DrawXBM(&u8g2,display+64,16,32,32,setting);//传入设置图标图片  
	u8g2_SendBuffer(&u8g2);                         //把要显示的信息写入缓存
}

void u8g2_Show_Astronaut(u8g2_t *u8g2, unsigned char i)
{
	u8g2_SetDrawColor(u8g2, 0);
	u8g2_DrawBox(u8g2, display, 0, 64, 64);
	u8g2_DrawXBM(u8g2, display, 0, 64, 64, Image[i]);
	u8g2_SendBuffer(u8g2);
	
}

void Show_Menu(Speed_ENUM Speed_choose)        // 显示菜单函数，参数为动态显示速度的枚举类型
{
     uint8_t i = 0;
    	while(1)
	{
          KeyNum = Key_GetNum();                     // 获取按键编号
		u8g2_Show_Astronaut(&u8g2, i);
		i++;
		if(i>=14)
		{
			i = 0;
		}
		Delay_ms(10);
          if(KeyNum ==1||KeyNum ==2||KeyNum ==3) break;
	}
     

     Game_Menu_Flag = KeyNum;                   // 将按键编号赋值给游戏菜单标志位
    
    if ((KeyNum == 1) && (display > -32))      // 如果按下了按键1并且显示位置大于-48
    {
        Picture_Flag++;                        // 图片标志位自增，用于切换显示"GAME","MESSAGE","SETTING"
        circle_num = 32 / Speed_choose;        // 根据速度选择设置循环次数，速度越慢动画越丝滑
        
        while (circle_num)                     // 当循环次数不为0时
        {
            u8g2_ClearBuffer(&u8g2);           // 清除显示缓存
            display = display-Speed_choose;     
            u8g2_SetDrawColor(&u8g2, 1); 
//            u8g2_DrawBox(&u8g2, display, 0, 64, 64);
//	       u8g2_DrawXBM(&u8g2, display, 0, 64, 64, Image[i]); 
            u8g2_DrawXBM(&u8g2, display + 64, 0, 64,64, setup);
            u8g2_SendBuffer(&u8g2); // 将缓存的内容发送到显示设备
            
            circle_num--; // 循环次数递减
        }
        
        KeyNum = 0; // 重置按键编号
    }
    else if ((KeyNum == 2) && (display < 32))  // 如果按下了按键2并且显示位置小于48
    {
        Picture_Flag--;                       // 图片标志位自减，用于切换显示"GAME","MESSAGE","SETTING"
        
        circle_num = 32 / Speed_choose;       // 根据速度选择设置循环次数
        while (circle_num)                    // 同上，向右移动图片
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
        KeyNum = 0;   // 重置按键编号
    }
    else ;           // 如果没有按键被按下，不执行任何操作
    
                     // 根据图片标志位的值，显示不同的菜单项
//    switch (Picture_Flag)
//    {
//        case 0:
//            // 显示"GAME"菜单项
//            u8g2_DrawStr(&u8g2, 52, 10, "MENU:");
//            u8g2_DrawStr(&u8g2, 82, 10, &words[0][0]); // 显示"功能菜单"里的文字说明
//            u8g2_SendBuffer(&u8g2);
//            Game_Menu(); // 调用游戏菜单函数
//            break;
//        
//        case 1:
//            // 显示"MESSAGE"菜单项
//            u8g2_DrawStr(&u8g2, 52, 10, "MENU:");
//            u8g2_DrawStr(&u8g2, 82, 10, &words[1][0]); // 显示"消息菜单"里的文字说明
//            u8g2_SendBuffer(&u8g2);
//            break;
//        
//        case 2:
//            // 显示"SETTING"菜单项
//            u8g2_DrawStr(&u8g2, 52, 10, "MENU:");
//            u8g2_DrawStr(&u8g2, 82, 10, &words[2][0]); // 显示"设置菜单"里的文字说明
//            u8g2_SendBuffer(&u8g2);
//            break;
//    }
}


void Game_Menu(void) 
{
	static char Box_x = 1;//设置小方框各种参数初始值
	static char Box_y = 14;
	static char Box_w = 84;
	static char Box_h = 13;
	       
	static char Box_x_trg;//设置小方框目标值
	static char Box_y_trg;
	static char Box_w_trg;
	static char Box_h_trg;
	
	static int8_t Box_Flag = 0;
	
	if(Game_Menu_Flag == 3)//确认键
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
			
			switch(Box_Flag)//获取方框参数目标值
			{
				case 0: Box_x_trg = 1;Box_y_trg = 14;Box_w_trg = sizeof("game1:FlyBird")*6;Box_h_trg = 13;break;
				case 1: Box_x_trg = 1;Box_y_trg = 27;Box_w_trg = sizeof("game2:Dinosaur Rex")*6;Box_h_trg = 13;break;
				case 2: Box_x_trg = 1;Box_y_trg = 38;Box_w_trg = sizeof("game1:Stick Fight")*6;Box_h_trg = 13;break;
				case 3: Box_x_trg = 1;Box_y_trg = 51;Box_w_trg = sizeof("game1:Tetris")*6;Box_h_trg = 12;break;
			}                              
		}               
	}  
	Game_Menu_Flag = 0;//重置	
	Show_Menu_Config();//回到主显示页面
	display = 48;
	Picture_Flag = 0;
}
void To_Game_Menu_Display(void)//菜单→游戏菜单过渡动画
{
	char Game_Menu_Display = 10;
	char Game_Menu_Display_trg =74;
	
	while(Game_Menu_Display != Game_Menu_Display_trg)
	{	
		
//		u8g2_ClearBuffer(&u8g2);
//		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"MENU:");//Y要变为0或72“MENU”才会完全消失
//		u8g2_DrawXBM(&u8g2,44,Game_Menu_Display+26,40,40,arrowhead);//传入箭头标志图片
//		u8g2_DrawXBM(&u8g2,display,Game_Menu_Display+6,32,32,game);//传入游戏图标图片
//		u8g2_DrawXBM(&u8g2,display+48,Game_Menu_Display+6,32,32,wechat);//传入信息图标图片
//		u8g2_DrawXBM(&u8g2,display+96,Game_Menu_Display+6,32,32,setting);//传入设置图标图片  
//		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
//		u8g2_SendBuffer(&u8g2);//把要显示的信息写入缓存
	}
	
		Game_Menu_Display = 74;	
		Game_Menu_Display_trg =10;

	while(Game_Menu_Display != Game_Menu_Display_trg)
	{	u8g2_ClearBuffer(&u8g2);
		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"GAME");//Game_Menu_Display+16+62为72，此时“Game”消失
		u8g2_DrawLine(&u8g2, 1, Game_Menu_Display+3, 128, Game_Menu_Display+3);
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+14,"game1:FlyBird");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+26,"game2:Dinosaur Rex");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+38,"game3:Stick Fight");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+50,"game4:Tetris");
		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
		u8g2_SendBuffer(&u8g2);//把要显示的信息写入缓存
	}	
}

void Game_To_Menu_Display(void)//游戏菜单→菜单过渡动画
{
	char Game_Menu_Display = 10;
	char Game_Menu_Display_trg =74;
	
	while(Game_Menu_Display != Game_Menu_Display_trg)
	{	
		u8g2_ClearBuffer(&u8g2);
		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"GAME");//Game_Menu_Display+16+62为72，此时“Game”消失
		u8g2_DrawLine(&u8g2, 1, Game_Menu_Display+3, 128, Game_Menu_Display+3);
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+14,"game1:FlyBird");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+26,"game2:Dinosaur Rex");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+38,"game3:Stick Fight");
		u8g2_DrawStr(&u8g2,3,Game_Menu_Display+50,"game4:Tetris");
		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
		u8g2_SendBuffer(&u8g2);//把要显示的信息写入缓存
	}
		Game_Menu_Display = 74;	
		Game_Menu_Display_trg =10;

//	while(Game_Menu_Display != Game_Menu_Display_trg)
//	{	
//		u8g2_ClearBuffer(&u8g2);
//		ui_run(&Game_Menu_Display,&Game_Menu_Display_trg,8);
//		u8g2_DrawStr(&u8g2,52,Game_Menu_Display,"MENU:");//Y要变为0或>=72“MENU”才会完全消失
//		u8g2_DrawXBM(&u8g2,44,Game_Menu_Display+26,40,40,arrowhead);//传入箭头标志图片
//		u8g2_DrawXBM(&u8g2,display,Game_Menu_Display+6,32,32,game);//传入游戏图标图片
//		u8g2_DrawXBM(&u8g2,display+48,Game_Menu_Display+6,32,32,wechat);//传入信息图标图片
//		u8g2_DrawXBM(&u8g2,display+96,Game_Menu_Display+6,32,32,setting);//传入设置图标图片  
//		u8g2_SendBuffer(&u8g2);//把要显示的信息写入缓存
//	}	
}

