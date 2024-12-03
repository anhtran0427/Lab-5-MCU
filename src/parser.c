/*
 * parser.c
 *
 *  Created on: Dec 3, 2024
 *      Author: ASUS
 */


#include "parser.h"
uint8_t command_flag=0;
uint8_t command_data[50]="";
int STATE_PARSE=IDLE_PARSE;
uint32_t ADC_value=10;
uint8_t str[50];
void command_parser_fsm(){
	switch (STATE_PARSE){
	case IDLE_PARSE:
		if (command_flag==1){
			STATE_PARSE=PARSE;
		}
		break;
	case PARSE:
		//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);

		if (strcmp((char*)command_data, "RST")==0){
			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			STATE_PARSE=SEND;
		}
		else{
			STATE_PARSE=CLEAR;
		}
		break;
	case SEND:
		ADC_value = getVal();
		int len=sprintf((char*)str, "!ADC=%d#\r\n", (int)ADC_value);
		send(str, len);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		strcpy((char*)str, "");

		command_flag=0;
		strcpy((char*)command_data,"");

		setTimer(15000);
		STATE_PARSE=WAIT;
		break;
	case WAIT:
		if (command_flag==1){
			command_flag=0;
			if (strcmp((char*)command_data, "OK")==0){
				STATE_PARSE=CLEAR;
				break;
			}
			strcpy((char*)command_data,"");
		}
		if (timerFlag==1){
			//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			int len=sprintf((char*)str, "!ADC=%d#\r\n", (int)ADC_value);
			send(str, len);
//			command_flag=0;
//			strcpy((char*)command_data,"");
			/*char* temp="IDLE_READ_FIND_END\r\n";
			send((uint8_t*)temp,strlen((char*)temp));*/
			setTimer(15000);
		}
		break;
	case CLEAR:
		command_flag=0;
		strcpy((char*)command_data,"");
		STATE_PARSE=IDLE_PARSE;
		break;
	default:
		break;
	}
}
