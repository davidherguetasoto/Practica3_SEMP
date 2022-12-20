/*
 * interfazHAL_fsm_muestreo.c
 *
 *  Created on: 17 dic. 2022
 *      Author: David
 */


#include "interfazHAL_fsm_muestreo.h"
#include "stm32f4_discovery_accelerometer.h"
#include <stdlib.h>

#define EXTREME 90
#define HIGH 60
#define NORMAL 30

typedef struct{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}boton_t;

typedef struct{
	TIM_HandleTypeDef* timer_pwm_salida;
	uint32_t channel;
}salida_t;

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

void pwmSalidaNormal(void* salida)
{
	salida_t *s = (salida_t*)salida;
	__HAL_TIM_SET_COMPARE(s->timer_pwm_salida, s->channel, NORMAL);
}

void pwmSalidaHigh(void* salida)
{
	salida_t *s = (salida_t*)salida;
	__HAL_TIM_SET_COMPARE(s->timer_pwm_salida, s->channel, HIGH);
}

void pwmSalidaExtreme(void* salida)
{
	salida_t *s = (salida_t*)salida;
	__HAL_TIM_SET_COMPARE(s->timer_pwm_salida, s->channel, EXTREME);
}

void pwmSalidaOff(void* salida)
{
	salida_t *s = (salida_t*)salida;
	__HAL_TIM_SET_COMPARE(s->timer_pwm_salida, s->channel, 0);
}

void togglePin(void* pin)
{
	boton_t *b = (boton_t*)pin;
	HAL_GPIO_TogglePin(b->GPIOx, b->GPIO_Pin);
}

void writePin(void* pin, int valor)
{
	boton_t *b = (boton_t*)pin;
	HAL_GPIO_WritePin(b->GPIOx, b->GPIO_Pin, valor);
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

fsm_procesamiento_t* fsm_procesamiento_new(uint8_t* activado, TIM_HandleTypeDef* tim_pwm_salida, uint32_t canal_tim_pwm, uint8_t FIFO_empty,  pullFIFO_p pull_FIFO)
{
	salida_t *s = (salida_t*)malloc(sizeof(salida_t));
	s ->timer_pwm_salida = tim_pwm_salida;
	s ->channel = canal_tim_pwm;
	return _fsm_procesamiento_new(activado,FIFO_empty,(void*)s,pwmSalidaNormal,pwmSalidaHigh,pwmSalidaExtreme,pull_FIFO,pwmSalidaOff);
}

void fsm_procesamiento_fire(fsm_procesamiento_t* this)
{
	_fsm_procesamiento_fire(this);
}

fsm_led_encendido_t* fsm_led_encendido_new (uint8_t* activado, uint8_t* flag_timer_led, GPIO_TypeDef* GPIOx_led, uint16_t GPIO_Pin_led, TIM_HandleTypeDef* timer_led)
{
	boton_t *b = (boton_t*)malloc(sizeof(boton_t));
	b->GPIO_Pin = GPIO_Pin_led;
	b->GPIOx = GPIOx_led;

	return _fsm_led_encendido_new(activado, flag_timer_led,(void*)b, (void*)timer_led, startTimer, stopTimer, setTimer, togglePin, writePin);
}

void fsm_led_encendido_fire(fsm_led_encendido_t* this)
{
	_fsm_fire_led_encendido(this);
}
