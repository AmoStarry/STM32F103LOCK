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
	u8g2_SetFontMode(&u8g2, 1);//设置字体模式，mode字体模式，启用（1）或禁用（0）透明模式
	u8g2_SetFontDirection(&u8g2, 0);//设置字体方向 
	u8g2_SetFont(&u8g2, u8g2_font_spleen6x12_mf);//设置字体格式
     
}

////参数1：移动的起始位置（左定点为基准） 参数2：方向（1左 -1右） 参数3：移动范围
//void animateDisplay(int8_t initialDisplay, int8_t direction, int8_t maxDisplay) {
//    int8_t display = initialDisplay;
//    while ((direction > 0 && display < maxDisplay) || (direction < 0 && display > -maxDisplay)) {
//        u8g2_ClearBuffer(&u8g2); // 清除显示缓存
//        u8g2_DrawXBM(&u8g2, 0 + direction * display, 16, 32, 32, password);
//        u8g2_DrawBox(&u8g2, 32 + direction * display, 0, 64, 64);
//        u8g2_DrawXBM(&u8g2, 32 + direction * display, 0, 64, 64, Image[i]);
//        u8g2_DrawXBM(&u8g2, 96 + direction * display, 16, 32, 32, setting);
//        u8g2_SendBuffer(&u8g2); // 把要显示的信息写入缓存
//        display += 3;           // 更新位置
//    }
//}	


void Show_Menu(Speed_ENUM Speed_choose)        // 显示菜单函数，参数为动态显示速度的枚举类型
{
     
    uint8_t index = 1; // 当前菜单索引，从0开始 
    uint8_t display =0;
    uint8_t key;

    while (1) 
    {
        key = Key_GetNum(); // 获取按键
                      
        if (key == 1)       // 检查按键，根据按键更新索引
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
                    u8g2_ClearBuffer(&u8g2);                        // 清除显示缓存
                    u8g2_DrawXBM(&u8g2, 0+display,16,32,32,password); 
                    u8g2_DrawBox(&u8g2,32+display, 0, 64, 64);
                    u8g2_DrawXBM(&u8g2,32+display, 0, 64, 64, Image[i]);
                    u8g2_DrawXBM(&u8g2,96+display,16,32,32,setting);
                    u8g2_SendBuffer(&u8g2);                         //把要显示的信息写入缓存                    
               };
               u8g2_ClearBuffer(&u8g2);                        // 清除显示缓存
               u8g2_DrawXBM(&u8g2,32,0,64,64,password_big);    //传入设置图标图片
               u8g2_SendBuffer(&u8g2);                         //把要显示的信息写入缓存
               break;
          case 1:
               u8g2_DrawXBM(&u8g2,0,16,32,32,password);        //传入密码图标图片
               u8g2_DrawXBM(&u8g2,96,16,32,32,setting);        //传入设置图标图片
               u8g2_SendBuffer(&u8g2);                         //把要显示的信息写入缓存
               i = (i + 1) % 14;
               u8g2_DrawBox(&u8g2, 32, 0, 64, 64);
               u8g2_DrawXBM(&u8g2, 32, 0, 64, 64, Image[i]);
               u8g2_SendBuffer(&u8g2);                         //把要显示的信息写入缓存
               u8g2_SetDrawColor(&u8g2, 1);
               Delay_ms(10); // 延时10ms          
               break;
          case 2:
               for(;display <32;display+=3)
               {
                    u8g2_ClearBuffer(&u8g2);                        // 清除显示缓存
                    u8g2_DrawXBM(&u8g2, 0-display,16,32,32,password);
                    u8g2_DrawBox(&u8g2,32-display, 0, 64, 64);
                    u8g2_DrawXBM(&u8g2,32-display, 0, 64, 64, Image[i]);
                    u8g2_DrawXBM(&u8g2,96-display,16,32,32,setting);
                    u8g2_SendBuffer(&u8g2);                         //把要显示的信息写入缓存
               }
               u8g2_ClearBuffer(&u8g2);                        // 清除显示缓存
               u8g2_DrawXBM(&u8g2,32,0,64,64,setup);           //传入设置图标图片
               u8g2_SendBuffer(&u8g2);                         //把要显示的信息写入缓存
               break;
        }
     }           
}


