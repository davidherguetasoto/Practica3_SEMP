/*
 * interfazHAL_fsm_muestreo.c
 *
 *  Created on: 17 dic. 2022
 *      Author: David
 */


#include "interfazHAL_fsm_muestreo.h"
#include "stm32f4_discovery_accelerometer.h"


void startTimer(TIM_HandleTypeDef* timer)
{
	HAL_TIM_Base_Start_IT(timer);
}

void stopTimer(TIM_HandleTypeDef* timer)
{
	HAL_TIM_Base_Stop(timer);
}

void setTimer(TIM_HandleTypeDef* timer, int counter)
{
	__HAL_TIM_SET_COUNTER(timer, counter);
}

void lecturaSensor(int16_t* buffer)
{
	BSP_ACCELERO_GetXYZ(buffer);
}

fsm_muestreo_t* fsm_muestreo_new(uint8_t* activado, uint8_t* flag_timer_muestreo,
		TIM_HandleTypeDef* timer, uint8_t FIFO_full, pushFIFO_p pushFIFO)
{
	return _fsm_muestreo_new(activado,flag_timer_muestreo,(void*)timer,startTimer, stopTimer,
			setTimer,FIFO_full, pushFIFO, lecturaSensor);
}

void fsm_muestreo_fire(fsm_muestreo_t* this)
{
	_fsm_muestreo_fire(this);
}
