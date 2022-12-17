/*
 * interfazHAL_fsm_muestreo.c
 *
 *  Created on: 17 dic. 2022
 *      Author: David
 */


#include "interfazHAL_fsm_muestreo.h"
#include "stm32f4_discovery_accelerometer.h"
#include <stdlib.h>

typedef struct{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}boton_t;


void startTimer(void* timer)
{
	HAL_TIM_Base_Start_IT((TIM_HandleTypeDef*)timer);
}

void stopTimer(void* timer)
{
	HAL_TIM_Base_Stop((TIM_HandleTypeDef*)timer);
}

void setTimer(void* timer, int counter)
{
	__HAL_TIM_SET_COUNTER((TIM_HandleTypeDef*)timer, counter);
}

int botonPulsado(void* boton)
{
	boton_t *bi = (boton_t*)boton;
	return(HAL_GPIO_ReadPin(bi->GPIOx, bi->GPIO_Pin));
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

fsm_boton_encendido_t* fsm_boton_encendido_new (uint8_t* activado, uint8_t* flag_timer_boton, GPIO_TypeDef* GPIOx_boton, uint16_t GPIO_Pin_boton, TIM_HandleTypeDef* timer_boton)
{
	boton_t *b = (boton_t*)malloc(sizeof(boton_t));
	b->GPIO_Pin = GPIO_Pin_boton;
	b->GPIOx = GPIOx_boton;

	return _fsm_boton_encendido_new(activado, flag_timer_boton,(void*)b, (void*)timer_boton, botonPulsado, startTimer, stopTimer, setTimer);
}

void fsm_boton_encendido_fire(fsm_boton_encendido_t* this)
{
	_fsm_fire_boton_encendido(this);
}
