#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <esp8266.h>
#include <Serial.h>
#include <Delay.h>
#include <OLED.h>
#include "core_json.h"

/*************************************/
uint8_t led_status =0;
uint8_t temp_value =60;
uint8_t humi_value =60;
/*************************************/
unsigned char receive_buf[512];	  //串口接收缓存数组
uint16_t receive_start =0;           //定义串口接收的标志位变量
uint16_t receive_count =0;           //定义串口接收字节计数

#define WIFI_SSID        "22"
#define WIFI_PASSWD      "11111111"

#define MQTT_CLIENT_ID   "k0ygtxfPbcQ.esp8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1712143269117|"   
#define MQTT_USER_NAME   "esp8266&k0ygtxfPbcQ"
#define MQTT_PASSWD      "deea2be94e549b8b9841e99567e0c6b04c08ad2353c0739e24c4ffd5d825b32d"
#define BROKER_ASDDRESS  "iot-06z00edcq1sto7u.mqtt.iothub.aliyuncs.com"
#define SUB_TOPIC        "/sys/k0ygtxfPbcQ/esp8266/thing/service/property/set"
#define PUB_TOPIC        "/sys/k0ygtxfPbcQ/esp8266/thing/event/property/post"
#define JSON_FORMAT      "{\\\"params\\\":{\\\"temp\\\":%d\\,\\\"humi\\\":%d\\}\\,\\\"version\\\":\\\"1.0.0\\\"}"

char AT_RESTORE[] =     {"AT+RESTORE\r\n"};
char AT_CWMODE[] =      {"AT+CWMODE=1\r\n"};
char AT_CIPSNTPCFG[] =  {"AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n"};
char AT_CWJAP[] =       {"AT+CWJAP=\""WIFI_SSID"\",\""WIFI_PASSWD"\"\r\n"};
char AT_MQTTUSERCFG[] = {"AT+MQTTUSERCFG=0,1,\"NULL\",\""MQTT_USER_NAME"\",\""MQTT_PASSWD"\",0,0,\"\"\r\n"};
char AT_MQTTCLIENTID[] ={"AT+MQTTCLIENTID=0,\""MQTT_CLIENT_ID"\"\r\n"};
char AT_MQTTCONN[] =    {"AT+MQTTCONN=0,\""BROKER_ASDDRESS"\",1883,1\r\n"};
char AT_MQTTSUB[] =     {"AT+MQTTSUB=0,\""SUB_TOPIC"\",1\r\n"};    

void esp8266_init(void)
{
//     printf("AT\r\n");
//     Delay_ms(1000);
//     printf("AT+RESTORE\r\n");
//     Delay_ms(1000);
//     printf("AT+CWMODE=1\r\n");
//     Delay_ms(1000);
//     printf("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
//     Delay_ms(1000);
//     printf("AT+CWJAP=\"22\",\"11111111\"\r\n");
//     Delay_ms(5000);
//     printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"esp8266&k0ygtxfPbcQ\",\"6f3afe7e1b5c81adca541957bb9774bbe1958c7b85c07c2737b0b13a75834e45\",0,0,\"\"\r\n");
//     Delay_ms(5000);
//     printf("AT+MQTTCLIENTID=0,\"k0ygtxfPbcQ.esp8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1712023569066|\"\r\n");
//     Delay_ms(5000);
//     printf("AT+MQTTCONN=0,\"iot-06z00edcq1sto7u.mqtt.iothub.aliyuncs.com\",1883,1\r\n");
//     Delay_ms(10000);
//     printf("AT+MQTTSUB=0,\"/sys/k0ygtxfPbcQ/esp8266/thing/service/property/set\",1\r\n");
//     Delay_ms(5000);
//     printf("AT+MQTTPUB=0,\"/sys/k0ygtxfPbcQ/esp8266/thing/event/property/post\",\"{\\\"params\\\":{\\\"temp\\\":88\\,\\\"humi\\\":66\\,\\\"led\\\":1}\\,\\\"version\\\":\\\"1.0.0\\\"}\",1,0\r\n");
//     Delay_ms(5000);

     Serial_SendString(AT_RESTORE);
     Timerout_exit(2,"1.RESET");
     Serial_SendString(AT_CWMODE);
     Timerout_exit(2,"2.MODE1");
     Serial_SendString(AT_CIPSNTPCFG);
     Timerout_exit(2,"3.ALIYUN_INIT");
     Serial_SendString(AT_CWJAP);
     Timerout_exit(2,"4.WIFI_SUCCESS");
     Serial_SendString(AT_MQTTUSERCFG);
     Timerout_exit(5,"5.MQTT USER");
     Serial_SendString(AT_MQTTCLIENTID);
     Timerout_exit(5,"6.MQTT CLIENTID");
     Serial_SendString(AT_MQTTCONN);
     Timerout_exit(5,"7.MQTT ALIYUN");
     Serial_SendString(AT_MQTTSUB);
     Timerout_exit(5,"8.SUB TOPIC");
     
     Delay_ms(1000);
     OLED_Clear();
     OLED_ShowString(2, 1, "ESP8266_INIT");
     Delay_ms(2000);
     OLED_Clear();
}

void esp8266_send_data(void)
{
     char send_databuf[256];
     sprintf((char *)send_databuf,"AT+MQTTPUB=0,\""PUB_TOPIC"\",\""JSON_FORMAT"\",0,0\r\n",temp_value,humi_value);
     Serial_SendString(send_databuf);
     Timerout_exit(3,"SEED SUCCESS");
     Delay_ms(2000);
     OLED_Clear();
}

void esp8266_receive_data(void)
{    
     uint8_t retval =0;
     int data_len =0;
     uint8_t data_body[128] ={0};
     
     if(receive_start == 1)
     {
          Delay_ms(50);
		if(strstr((const char*)receive_buf,"+MQTTSUBRECV:"))
		{
			sscanf((const char *)receive_buf,"+MQTTSUBRECV:0,\""SUB_TOPIC"\",%d,%s",&data_len,data_body);
               if(strlen((const char*)data_body)== data_len)
			{
                    retval = parse_json_msg(data_body,data_len);
                    if(retval ==2)
                    {    
                         OLED_ShowString(2,1,"JSON_ERROR");
                    }
                    memset(receive_buf, 0x00, sizeof(receive_buf));
                    receive_count =0;
                    receive_start =0;
			}
               
          }
     }
     
}
uint8_t parse_json_msg(uint8_t *json_msg, uint8_t json_len)
{
    uint8_t retval = 0;
    JSONStatus_t result;
    char *value;
    size_t valueLength;

    result = JSON_Validate((const char *)json_msg, json_len);    // 验证 JSON 消息是否有效
    if (result != JSONSuccess)
    {
        return 1; // JSON 验证失败
    }

    const char *data[3] = {"params.led", "params.temp", "params.humi"}; // 定义要查找的键数组
    for (int i = 0; i < 3; ++i)
    {
        result = JSON_Search((char *)json_msg, json_len, data[i], strlen(data[i]), &value, &valueLength);
        if (result == JSONSuccess)
        {
            char save = value[valueLength];          // 处理找到的值
            value[valueLength] = '\0';
            switch (i)
            {
                case 0: // "params.led"
                    led_status = atoi(value);
                    OLED_ShowNum(1, 8, led_status, 2);
                    break;
                case 1: // "params.temp"
                    temp_value = atof(value);
                    OLED_ShowNum(2, 8, temp_value, 2);
                    break;
                case 2: // "params.hum"
                    humi_value = atof(value);
                    OLED_ShowNum(3, 8, humi_value, 2);
                    break;
            }
            value[valueLength] = save;
        }
        else
        {
            retval = 2; // 查询键失败
            break;      // 如果任何键未找到，退出循环
        }
    }

    return retval; // 返回解析结果
}

void Timerout_exit(uint16_t time,char *message)
{
     uint16_t count =0;
     while(1)
     {
          if(receive_start == 0)
          {
              count++;
              Delay_ms(1000); 
              if(count >= time) 
              {
                  OLED_ShowString(4, 2, "Timeout ERROR");
              }
          }
          if(strstr((const char*)receive_buf, "OK"))
          {
                   OLED_ShowString(2, 1, message);
                   memset(receive_buf, 0x00, sizeof(receive_buf));
                   receive_count =0;
                   receive_start =0;
                   break;
          }
     }

}
