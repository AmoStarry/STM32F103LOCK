#include <esp8266.h>
#include <Serial.h>
#include <Delay.h>

#define WIFI_SSID        "11"
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
     Delay_ms(1000);
     Serial_SendString(AT_CWMODE);
     Delay_ms(1000);
     Serial_SendString(AT_CIPSNTPCFG);
     Delay_ms(1000);
     Serial_SendString(AT_CWJAP);
     Delay_ms(5000);
     Serial_SendString(AT_MQTTUSERCFG);
     Delay_ms(1000);
     Serial_SendString(AT_MQTTCLIENTID);
     Delay_ms(5000);
     Serial_SendString(AT_MQTTCONN);
     Delay_ms(5000);
     Serial_SendString(AT_MQTTSUB);
}
