/*
 * timer.c
 *
 *  Created on: Dec 3, 2024
 *      Author: ASUS
 */
#include "timer.h"

uint8_t timerCounter;
uint8_t timerFlag=0;

void setTimer(int ms){
	timerCounter = ms / TIMER_CYCLE_2 ;
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	timerFlag = 0;
}

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	if (htim->Instance==TIM2){
		if (timerCounter>0){
			timerCounter--;
			if (timerCounter==0){

				timerFlag=1;
			}
		}
	}

 }
