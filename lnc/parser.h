/*
 * parser.h
 *
 *  Created on: Dec 3, 2024
 *      Author: ASUS
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_
#include "common.h"
#include "main.h"
extern uint8_t command_flag;
extern uint8_t command_data[50];
void command_parser_fsm();
#endif /* INC_PARSER_H_ */
