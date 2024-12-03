/*
 * term.h
 *
 *  Created on: Dec 3, 2024
 *      Author: ASUS
 */

#ifndef INC_TERM_H_
#define INC_TERM_H_
#include "main.h"
#include "common.h"
#define MAX_BUFFER_SIZE 30

extern uint8_t buffer[MAX_BUFFER_SIZE];

extern uint8_t index_buffer_write;


extern uint8_t buffer_flag ;


extern void init_buffer_uart();
extern void uart_communiation_fsm();

#endif /* INC_TERM_H_ */
