/*
 * task_fsm.h
 *
 *  Created on: 18 dic. 2022
 *      Author: David
 */

#ifndef INC_TASK_FSM_H_
#define INC_TASK_FSM_H_

#include "interfazHAL_fsm_muestreo.h"
#include "cmsis_os.h"

typedef struct{
	osThreadAttr_t task_attributes;
	fsm_boton_encendido_t *f;
	uint32_t delay;
    GPIO_TypeDef * port;
    uint16_t pin;
    TIM_HandleTypeDef* timer_boton;
    uint8_t *activado;
    uint8_t* flag_timer_boton;
}task_fsm_boton_encendido_t;

void task_fsm_boton_encendido_create(void *argument);
#endif /* INC_TASK_FSM_H_ */
