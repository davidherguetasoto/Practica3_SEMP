/*
 * interfaz_hal.h
 *
 *  Created on: 15 dic. 2022
 *      Author: andre
 */

#ifndef INC_INTERFAZ_HAL_H_
#define INC_INTERFAZ_HAL_H_

#include "stm32f4xx.h"

typedef GPIO_TypeDef GPIO_TypeDef_t;
typedef TIM_HandleTypeDef TIM_HandleTypeDef_t;

void start_timer(TIM_HandleTypeDef *htim);
void stop_timer(TIM_HandleTypeDef *htim);
void reset_timer(TIM_HandleTypeDef *htim, uint16_t counter);

void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void toggle_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* INC_INTERFAZ_HAL_H_ */
