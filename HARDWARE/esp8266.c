#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <esp8266.h>
#include <Serial.h>
#include <Delay.h>
#include <OLED.h>

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
