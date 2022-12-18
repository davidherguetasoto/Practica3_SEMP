/*
 * interfazHAL_fsm_muestreo.h
 *
 *  Created on: 16 dic. 2022
 *      Author: David
 */

#ifndef INC_INTERFAZHAL_FSM_MUESTREO_H_
#define INC_INTERFAZHAL_FSM_MUESTREO_H_

#include "fsm_muestreo.h"
#include "fsm_boton_encendido.h"
#include "fsm_procesamiento.h"
#include "stm32f4xx.h"

fsm_muestreo_t* fsm_muestreo_new(uint8_t* activado, uint8_t* flag_timer_muestreo,
		TIM_HandleTypeDef* timer, uint8_t FIFO_full, pushFIFO_p pushFIFO);
void fsm_muestreo_fire(fsm_muestreo_t* this);

fsm_boton_encendido_t* fsm_boton_encendido_new (uint8_t* activado, uint8_t* flag_timer_boton,
		GPIO_TypeDef* GPIOx_boton, uint16_t GPIO_Pin_boton, TIM_HandleTypeDef* timer_boton);
void fsm_boton_encendido_fire(fsm_boton_encendido_t* this);

fsm_procesamiento_t* fsm_procesamiento_new(uint8_t* activado, TIM_HandleTypeDef* tim_pwm_salida, uint32_t canal_tim_pwm, uint8_t FIFO_empty,  pullFIFO_p pull_FIFO);
void fsm_procesamiento_fire(fsm_procesamiento_t* this);

#endif /* INC_INTERFAZHAL_FSM_MUESTREO_H_ */
