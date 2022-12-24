/*
 * task_fsm.h
 *
 *  Created on: 18 dic. 2022
 *      Author: David
 */

#ifndef INC_TASK_FSM_H_
#define INC_TASK_FSM_H_

#include <interfazHAL.h>
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

typedef struct{
	osThreadAttr_t task_attributes;
	fsm_muestreo_t *f;
	uint32_t delay;
	TIM_HandleTypeDef* timer_muestreo;
	uint8_t *activado;
	uint8_t* flag_timer_muestreo;
}task_fsm_muestreo_t;

typedef struct{
	osThreadAttr_t task_attributes;
	fsm_procesamiento_t *f;
	uint32_t delay;
	TIM_HandleTypeDef* timer_pwm_salida;
	uint32_t canal_timer_pwm;
	uint8_t *activado;
}task_fsm_procesamiento_t;

typedef struct{
	osThreadAttr_t task_attributes;
	fsm_led_encendido_t *f;
	uint32_t delay;
	GPIO_TypeDef * GPIOx_led;
	uint16_t GPIO_Pin_led;
	TIM_HandleTypeDef* timer_led;
	uint8_t *activado;
	uint8_t* flag_timer_led;
}task_fsm_led_encendido_t;

void task_fsm_boton_encendido_create(void *argument);
void task_fsm_muestreo_create(void *argument);
void task_fsm_procesamiento_create(void *argument);
void task_fsm_led_encendido_create(void *argument);

#endif /* INC_TASK_FSM_H_ */
