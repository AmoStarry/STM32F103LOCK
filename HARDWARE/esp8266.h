#ifndef __ESP8266_H
#define __ESP8266_H
#include "stm32f10x.h"                  // Device header

void esp8266_init(void);
void Timerout_exit(uint16_t time,char *message);
void esp8266_send_data(void);
void esp8266_receive_data(void);
uint8_t parse_json_msg(uint8_t *json_msg, uint8_t json_len);
#endif
