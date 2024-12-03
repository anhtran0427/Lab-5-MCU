/*
 * timer.h
 *
 *  Created on: Dec 3, 2024
 *      Author: ASUS
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

#define TIMER_CYCLE_2 10

/* Variables */
extern uint8_t timerFlag;
extern void setTimer(int ms);
#endif /* INC_TIMER_H_ */
