#include <esp8266.h>
#include <Serial.h>
#include <Delay.h>

void esp8266_init(void)
{
     printf("AT\r\n");
     Delay_ms(1000);
     printf("AT+RESTORE\r\n");
     Delay_ms(1000);
     printf("AT+CWMODE=1\r\n");
     Delay_ms(1000);
     printf("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
     Delay_ms(1000);
     printf("AT+CWJAP=\"22\",\"11111111\"\r\n");
     Delay_ms(5000);
     printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"esp8266&k0ygtxfPbcQ\",\"6f3afe7e1b5c81adca541957bb9774bbe1958c7b85c07c2737b0b13a75834e45\",0,0,\"\"\r\n");
     Delay_ms(5000);
     printf("AT+MQTTCLIENTID=0,\"k0ygtxfPbcQ.esp8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1712023569066|\"\r\n");
     Delay_ms(5000);
     printf("AT+MQTTCONN=0,\"iot-06z00edcq1sto7u.mqtt.iothub.aliyuncs.com\",1883,1\r\n");
     Delay_ms(10000);
     printf("AT+MQTTSUB=0,\"/sys/k0ygtxfPbcQ/esp8266/thing/service/property/set\",1\r\n");
//     Delay_ms(5000);
//     printf("AT+MQTTPUB=0,\"/sys/k0ygtxfPbcQ/esp8266/thing/event/property/post\",\"{\\\"params\\\":{\\\"temp\\\":88\\,\\\"humi\\\":66\\,\\\"led\\\":1}\\,\\\"version\\\":\\\"1.0.0\\\"}\",1,0\r\n");
//     Delay_ms(5000);
}
