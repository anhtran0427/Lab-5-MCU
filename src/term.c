/*
 * term.c
 *
 *  Created on: Dec 3, 2024
 *      Author: ASUS
 */
#include "term.h"



int STATE_READ=IDLE_READ;

uint8_t buffer[MAX_BUFFER_SIZE];

uint8_t index_buffer_write = 0;
uint8_t index_buffer_read=0;

uint8_t buffer_flag = 0;
//uint8_t buffer_full=0;

uint8_t command_buffer[50]="";

uint8_t command_ready=0;

void init_buffer_uart(){
	for (int i=0;i<MAX_BUFFER_SIZE;i++){
		buffer[i]=0;
	}
}



void uart_communiation_fsm(){
	switch (STATE_READ){
	case IDLE_READ:
		if (buffer_flag==1 && command_flag ==0){

			if (command_ready==1){
				//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
				//char* temp="IDLE_READ_FIND_END\r\n";
				//send((uint8_t*)temp,strlen((char*)temp));
				STATE_READ=FIND_END;
			}
			else{
				//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
				//char* temp="IDLE_READ_FIND_START\r\n";
				//send((uint8_t*)temp,strlen((char*)temp));
				STATE_READ=FIND_START;
			}
		}
		break;
	case FIND_START:
		//char* temp="hi";
		//send((uint8_t*)temp,strlen((char*)temp));
		send(&buffer[index_buffer_read],1);
		if (buffer[index_buffer_read]=='!'){
			command_ready=1;
			buffer[index_buffer_read]='\0';
			index_buffer_read++;
			if(index_buffer_read == MAX_BUFFER_SIZE){
						index_buffer_read = 0;
			}

			//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			STATE_READ=FIND_END;
		}
		else if (buffer[index_buffer_read]=='\0'){
			buffer_flag=0;
			//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			STATE_READ=IDLE_READ;
		}
		else{
			buffer[index_buffer_read]='\0';
			index_buffer_read++;
			if(index_buffer_read == MAX_BUFFER_SIZE){
					index_buffer_read = 0;
			}
		}
		break;
	case FIND_END:
		send(&buffer[index_buffer_read],1);
		if (buffer[index_buffer_read]=='!'){
			strcpy((char*)command_buffer,"");

			buffer[index_buffer_read]='\0';
			index_buffer_read++;
			if(index_buffer_read == MAX_BUFFER_SIZE){
					index_buffer_read = 0;
			}
			//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			STATE_READ=FIND_END;
		}
		else if (buffer[index_buffer_read]=='#'){
			command_ready=0;
			buffer[index_buffer_read]='\0';
			index_buffer_read++;
			if(index_buffer_read == MAX_BUFFER_SIZE){
				index_buffer_read = 0;
			}
			//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			STATE_READ=COMMAND;
		}
		else if (buffer[index_buffer_read]=='\0'){
			buffer_flag=0;
			command_ready=1;
			//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			STATE_READ=IDLE_READ;
		}
		else if (strlen((char*)command_buffer)==50){
			command_ready=0;
			//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			STATE_READ=FIND_START;
		}
		else{
			strncat((char*)command_buffer, (char*)&buffer[index_buffer_read], 1);
			buffer[index_buffer_read]='\0';
			index_buffer_read++;
			if(index_buffer_read == MAX_BUFFER_SIZE){
					index_buffer_read = 0;
			}
		}
		break;
	case COMMAND:
		//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		command_flag=1;
		command_ready=0;
		strcpy((char*)command_data,(char*)command_buffer);
		send(command_data,strlen((char*)command_data));
		char* a="\r\n";
		send((uint8_t*)a,strlen((char*)a));
		strcpy((char*)command_buffer,"");
		STATE_READ=IDLE_READ;
		break;
	default:
		break;
	}

}
