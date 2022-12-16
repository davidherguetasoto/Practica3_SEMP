/*
 * interfaz_hal.c
 *
 *  Created on: 15 dic. 2022
 *      Author: andre
 */

#include "interfaz_hal.h"

void start_timer(TIM_HandleTypeDef *htim)
{
	__HAL_TIM_SET_COUNTER(htim, 0); //Reinicio a cero del temporizador del LED
	HAL_TIM_Base_Start_IT(htim); //Temporizador LED
}

void toggle_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}

void reset_timer(TIM_HandleTypeDef *htim, uint16_t counter)
{
	__HAL_TIM_SET_COUNTER(htim, counter);
}

void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}

void stop_timer(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Stop_IT(htim);
}
