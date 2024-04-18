#include <string.h>
#include "Menu.h"
#include "Key.h"
#include "u8g2.h"
#include "picture.h"
#include <stdio.h>
#include "Delay.h"
#include "keyboard.h"

extern u8g2_t u8g2;      // 声明一个外部的显示对象
uint8_t index_cmp = 1;       // 当前菜单选项，从1开始
uint8_t key;             // 用于存储按键值
uint8_t i = 0;           // 通用索引或计数器
uint8_t PWSend[7] = {0}; // 密码输入数组，最后一位为'\0'作为字符串结束符
uint8_t PWRecv[7] = {'1', '1', '1', '1', '1', '1', '\0'}; // 密码存储数组，最后一位为'\0'作为字符串结束符

void Show_Menu_Config(void)
{
    u8g2_SetFontMode(&u8g2, 1);             // 设置字体模式，1为覆盖模式（不透明），0为透明模式
    u8g2_SetFontDirection(&u8g2, 0);        // 设置字体方向
    u8g2_SetFont(&u8g2, u8g2_font_hapiwan); // 设置为一个示例字体
}


void ui_run(char* a, char* a_trg, int b)
{
    if (*a < *a_trg)     // 如果当前值小于目标值
    {
        *a += b;         // 增加步长
        if (*a > *a_trg) // 防止增加过头
            *a = *a_trg; // 设置为目标值
    }
    else if (*a > *a_trg) // 如果当前值大于目标值
    {
        *a -= b;         // 减少步长
        if (*a < *a_trg) // 防止减少过头
            *a = *a_trg; // 设置为目标值
    }
}



// 参数1：方向（1为正，-1为负）动画的方向（正数向右，负数向左）
// 参数2：动画的范围
void animateDisplay(int8_t direction, int8_t maxDisplay) 
{
    int8_t display = 0;
    while ((direction > 0 && display < maxDisplay) || (direction < 0 && display > -maxDisplay)) {
        u8g2_ClearBuffer(&u8g2);  // 清除显示缓冲区
        u8g2_DrawXBM(&u8g2, 0 + display, 16, 32, 32, password);
        u8g2_DrawBox(&u8g2, 32 + display, 0, 64, 64);
        u8g2_DrawXBM(&u8g2, 32 + display, 0, 64, 64, Image[i]);
        u8g2_DrawXBM(&u8g2, 96 + display, 16, 32, 32, setting);
        u8g2_SendBuffer(&u8g2);   // 将显示的信息写入显示缓冲区
        display += direction * 3; // 更新位置
    }
    u8g2_ClearBuffer(&u8g2);      // 清除显示缓冲区
}



void Show_Menu(Speed_ENUM Speed_choose) // 显示菜单函数，参数为动态显示的速度等级
{   
    while (1) 
    {
        key = Key_GetNum(); // 获取按键值
        if (key == 1) // 左按键，根据按键值更新选项
        {   
            if (index_cmp == 0) {
                index_cmp = 1;
                animateDisplay(-1, 32); // 当 index_cmp 为 0 时执行动画函数
            } 
            else {
                index_cmp = index_cmp - 1;
                animateDisplay(1, 32);  // 当 index_cmp 不为 0 时执行动画函数
            }
        } 
        else if (key == 2) 
        {
            if (index_cmp == 2) {
                index_cmp = 0;
                animateDisplay(1, 32); // 当 index_cmp 不为 0 时执行动画函数
            } 
            else {
                index_cmp = index_cmp + 1; // 更新索引
                animateDisplay(-1, 32); // 当 index_cmp 为 0 时执行动画函数
            }
        }

        else if (key == 3)
        {
            Input_passwrod();
        }
        
        switch(index_cmp)
        {
            case 0:
                u8g2_ClearBuffer(&u8g2); // 清除显示缓冲区
                u8g2_DrawXBM(&u8g2, 32, 0, 64, 64, password_big); // 传输密码大图标
                u8g2_SendBuffer(&u8g2); // 将显示的信息写入显示缓冲区
                Modify_password();
                break;
            case 1:
                u8g2_DrawUTF8(&u8g2, 25, 22, "%");
                u8g2_DrawXBM(&u8g2, 0, 32, 32, 32, humi); // 传输湿度图标
                u8g2_DrawUTF8(&u8g2, 115, 22, ".C");
                u8g2_DrawXBM(&u8g2, 96, 32, 32, 32, temp); // 传输温度图标
                u8g2_SendBuffer(&u8g2); // 将显示的信息写入显示缓冲区
                i = (i + 1) % 14;
                u8g2_DrawBox(&u8g2, 32, 0, 64, 64);
                u8g2_DrawXBM(&u8g2, 32, 0, 64, 64, Image[i]);
                u8g2_SendBuffer(&u8g2); // 将显示的信息写入显示缓冲区
                u8g2_SetDrawColor(&u8g2, 1);
                Delay_ms(10); // 延时10ms
                break;
            case 2:
                u8g2_ClearBuffer(&u8g2); // 清除显示缓冲区
                u8g2_DrawXBM(&u8g2, 32, 0, 64, 64, setup); // 传输设置图标
                u8g2_SendBuffer(&u8g2);
                setup_Menu();
                break;
            default:break;
        }
    }           
}


void setup_Menu(void) 
{   
    static char Box_x = 1;  // 设置小方框的初始位置
    static char Box_y = 14;
    static char Box_w = 84;
    static char Box_h = 13;
    
    static char Box_x_trg;  // 设置小方框的目标位置
    static char Box_y_trg;
    static char Box_w_trg;
    static char Box_h_trg;
    

    static int8_t Box_Flag = 0;
    key = Key_GetNum(); // 获取按键值
    if(key == 3)        // 确认键
    {
        while(1)
        {   
            key = Key_GetNum(); 
            u8g2_ClearBuffer(&u8g2);
            u8g2_DrawUTF8(&u8g2,3,15,"添加指纹");
            u8g2_DrawUTF8(&u8g2,3,30,"删除指纹");
            u8g2_DrawUTF8(&u8g2,3,45,"删除全部指纹");
            u8g2_DrawXBM(&u8g2,3,52,16,16,quit);

            ui_run(&Box_x, &Box_x_trg,1);   // 更新UI元素位置            
            ui_run(&Box_y, &Box_y_trg,1);
            ui_run(&Box_w, &Box_w_trg,2);
            ui_run(&Box_h, &Box_h_trg,1);
            
            u8g2_DrawFrame(&u8g2, Box_x, Box_y, Box_w, Box_h); // 绘制UI框架
            u8g2_SendBuffer(&u8g2);
            
            if (key == 1) 
            { 
                Box_Flag = (Box_Flag == 0) ? 3 : Box_Flag - 1; 
            }
            else if (key == 2) 
            {  
                Box_Flag = (Box_Flag == 3) ? 0 : Box_Flag + 1; 
            }           
            switch(Box_Flag) 
            {
                case 0: Box_x_trg = 1; Box_y_trg = 1; Box_w_trg =  sizeof("添加指纹")*6; Box_h_trg = 16;
                        
                        break;
                case 1: Box_x_trg = 1; Box_y_trg = 16; Box_w_trg = sizeof("删除指纹")*6; Box_h_trg = 16; break;
                case 2: Box_x_trg = 1; Box_y_trg = 31; Box_w_trg = sizeof("删除全部指纹")*6; Box_h_trg = 16; break;
                case 3: Box_x_trg = 1; Box_y_trg = 50; Box_w_trg = sizeof("输出")*6; Box_h_trg = 13;
                        key = Key_GetNum();
                        if(key == 3)
                        {
                            index_cmp = 1;  
                        }
                        break;
            } 
            if(index_cmp == 1)
            {
                u8g2_ClearBuffer(&u8g2);
                break; // 退出循环
            }               
        }               
    }
    else if(key == 1 || key == 2)
    {
        index_cmp = 1; // 返回到主界面
        animateDisplay(1, 32);
    }
    
}


void Input_passwrod(void)
{
     uint8_t pos;
     uint8_t count = 0;
     uint8_t password_length = 0;
     u8g2_ClearBuffer(&u8g2);             
     u8g2_DrawUTF8(&u8g2,30,15,"输入密码");
     u8g2_DrawFrame(&u8g2, 30, 30, 6 * 12 + 2, 17);
     u8g2_SendBuffer(&u8g2);     
     while(1)
     {
          pos = get_key_board();
          if(pos !=0)
          {
               if(password_length <= 6) // 防止数组越界
               {
                 PWSend[password_length] = pos; // 将字符存入数组
                 char str[2] = {pos, '\0'};     // 创建一个临时字符串用于显示
                 u8g2_DrawStr(&u8g2, 30 + 3 + (password_length * 12), 30 + 15, str);
                 u8g2_SendBuffer(&u8g2);
                 Delay_ms(800);
                 u8g2_SetDrawColor(&u8g2, 0); // 设置绘制颜色为黑色
                 u8g2_DrawBox(&u8g2, 30 + 3 +(password_length * 12), 30 + 3,10,12);
                 u8g2_SetDrawColor(&u8g2, 1); // 设置绘制颜色为黑色
                 u8g2_DrawStr(&u8g2, 30 + 3 + (password_length * 12), 30 + 15, "*");
                 password_length++;
                 u8g2_SendBuffer(&u8g2);
               }
               
              if(password_length == strlen((char *)PWRecv))   // 当输入的密码长度等于预设密码长度时，进行比较
              {
                  if(!strcmp((char *)PWRecv, (char *)PWSend)) // 密码匹配
                  {
                      u8g2_ClearBuffer(&u8g2);
                      u8g2_DrawXBM(&u8g2,48,5,32,32,success);
                      u8g2_DrawUTF8(&u8g2,30,55,"验证成功");
                      u8g2_SendBuffer(&u8g2);
                      Delay_ms(1500);
                      u8g2_ClearBuffer(&u8g2);
                      break; 
                  }
                  else
                  {   
                      count++;
                      u8g2_ClearBuffer(&u8g2);
                      u8g2_DrawXBM(&u8g2,48,5,32,32,fail);
                      u8g2_DrawUTF8(&u8g2,30,55,"验证失败");
                      u8g2_SendBuffer(&u8g2);
                      Delay_ms(1500);
                      u8g2_ClearBuffer(&u8g2);                       
                      u8g2_DrawUTF8(&u8g2,30,15,"重新输入");
                      u8g2_DrawFrame(&u8g2, 30, 30, 6 * 12 + 2, 17);
                      u8g2_SendBuffer(&u8g2);                         
                      memset(PWSend, 0 ,sizeof(PWSend)); // 清除错误密码
                      password_length = 0; // 重置密码长度
                      if(count >=2) 
                      {
                           u8g2_ClearBuffer(&u8g2);
                           break;
                      }
                  }
              }
          }
     }
     
}

void Modify_password(void)
{
     uint8_t pos;
     uint8_t count = 0;
     uint8_t password_length = 0;
     key = Key_GetNum(); // 获取按键值
     if(key == 3)        // 确认键
     {
          u8g2_ClearBuffer(&u8g2); 
          u8g2_DrawUTF8(&u8g2,30,15,"输入密码");
          u8g2_DrawFrame(&u8g2, 30, 30, 6 * 12 + 2, 17);
          u8g2_SendBuffer(&u8g2);  
          
          while(1)
          {
               pos = get_key_board();
               if(pos !=0)
               {
                    if(password_length <= 6) // 防止数组越界
                    {
                      PWSend[password_length] = pos; // 将字符存入数组
                      char str[2] = {pos, '\0'};     // 创建一个临时字符串用于显示
                      u8g2_DrawStr(&u8g2, 30 + 3 + (password_length * 12), 30 + 15, str);
                      u8g2_SendBuffer(&u8g2);
                      Delay_ms(800);
                      u8g2_SetDrawColor(&u8g2, 0); // 设置绘制颜色为黑色
                      u8g2_DrawBox(&u8g2, 30 + 3 +(password_length * 12), 30 + 3,10,12);
                      u8g2_SetDrawColor(&u8g2, 1); // 设置绘制颜色为黑色
                      u8g2_DrawStr(&u8g2, 30 + 3 + (password_length * 12), 30 + 15, "*");
                      password_length++;
                      u8g2_SendBuffer(&u8g2);
                    }
                    
                   if(password_length == strlen((char *)PWRecv))   // 当输入的密码长度等于预设密码长度时，进行比较
                   {
                       if(!strcmp((char *)PWRecv, (char *)PWSend)) // 密码匹配
                       {
                           u8g2_ClearBuffer(&u8g2);
                           u8g2_DrawXBM(&u8g2,48,5,32,32,success);
                           u8g2_DrawUTF8(&u8g2,30,55,"验证成功");
                           u8g2_SendBuffer(&u8g2);
                           Delay_ms(1500);
                           PWRecv_password();
                           break;
                       }
                       else
                       {   
                           count++;
                           u8g2_ClearBuffer(&u8g2);
                           u8g2_DrawXBM(&u8g2,48,5,32,32,fail);
                           u8g2_DrawUTF8(&u8g2,30,55,"验证失败");
                           u8g2_SendBuffer(&u8g2);
                           Delay_ms(1500);
                           u8g2_ClearBuffer(&u8g2);                       
                           u8g2_DrawUTF8(&u8g2,30,15,"重新输入");
                           u8g2_DrawFrame(&u8g2, 30, 30, 6 * 12 + 2, 17);
                           u8g2_SendBuffer(&u8g2);                         
                           memset(PWSend, 0 ,sizeof(PWSend)); // 清除错误密码
                           password_length = 0; // 重置密码长度
                           if(count >=3) 
                           {
                                u8g2_ClearBuffer(&u8g2);
                                break;
                           }
                       }
                   }
               }
          }
    }
    else if(key == 1 || key == 2)
    {
        index_cmp = 1; // 返回到主界面
        animateDisplay(-1, 32);
    }
}

void PWRecv_password(void)
{
     while(1)
     {
          uint8_t pos;
          uint8_t confirm_num =0;
          uint8_t password_length = 0;
          u8g2_ClearBuffer(&u8g2);             
          u8g2_DrawUTF8(&u8g2,30,15,"输入密码");
          u8g2_DrawFrame(&u8g2, 30, 30, 6 * 12 + 2, 17);
          u8g2_DrawXBM(&u8g2,3,52,16,16,quit);
          u8g2_SendBuffer(&u8g2);       
          memset(PWRecv, 0 ,sizeof(PWRecv)); // 清除原来密码
          while (password_length < 6) 
          {
             pos = get_key_board(); // 获取按键值
             if (pos != 0) {
                 PWRecv[password_length] = pos; // 将字符存入数组
                 char str[2] = {pos, '\0'}; // 创建一个临时字符串用于显示
                 u8g2_DrawStr(&u8g2, 30 + 3 + (password_length * 12), 30 + 15, str);
                 password_length++; // 增加已输入密码的长度
                 u8g2_SendBuffer(&u8g2);
             }
          }
          PWRecv[password_length] = '\0'; // 设置字符串结束符
          if(pos == '#')
          {
               u8g2_SetDrawColor(&u8g2, 0); // 设置绘制颜色为黑色
               u8g2_DrawBox(&u8g2, 30 +3 , 30 + 3, 6*12 , 12);
               u8g2_SetDrawColor(&u8g2, 1); // 设置绘制颜色为黑色
               memset(PWRecv, 0 ,sizeof(PWRecv)); // 清除原来密码
               password_length = 0; // 重置密码长度
          }
          if(password_length == 6)
          {
               while(1)
               {  
                    confirm_num = Key_GetNum(); // 获取按键值                    
                    if(confirm_num == 3)        // 确认键
                    {
                         u8g2_DrawFrame(&u8g2, 1, 50, 20, 13);
                         u8g2_SendBuffer(&u8g2);
                         Delay_ms(1500);
                         u8g2_ClearBuffer(&u8g2);
                         index_cmp =1;
                         break;
                    }
               }
               break;
          }
     }
}
