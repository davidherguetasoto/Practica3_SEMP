/*
 * fsm_led_encendido.c
 *
 *  Created on: Dec 15, 2022
 *      Author: andre
 */

#include "fsm_led_encendido.h"
#include <stdlib.h>

fsm_led_encendido_t* fsm_led_encendido_new (uint32_t delay, GPIO_TypeDef* port, uint16_t pin, uint8_t flag_timer_led, TIM_HandleTypeDef *timer_led, uint8_t activado)
{
	fsm_led_encendido_t* this = (fsm_led_encendido_t*) malloc (sizeof (fsm_led_encendido_t));
	this->f = fsm_new(led);
	fsm_led_encendido_init(this, delay, port, pin, flag_timer_led, timer_led, activado);
	return this;
}

void fsm_led_encendido_init (fsm_led_encendido_t* this, uint32_t delay, GPIO_TypeDef* puerto, uint16_t pin, uint8_t flag_timer_led, TIM_HandleTypeDef* timer_led, uint8_t activado)
{
	//fsm_init(this->fsm_led_encendido,tt);
	this->delay = delay;
	this->puerto = puerto;
	this->pin = pin;
	this->flag_timer_led = flag_timer_led;
	this->activado = activado;
	this->timer_led = timer_led;
}

void fsm_fire_led_encendido (fsm_led_encendido_t* this)
{
	fsm_fire(this->f);
}

//FUNCIONES DE TRANSICION
static int activado_on (fsm_led_encendido_t* this)
{
	return this->activado;
}

static int led_actualizacion (fsm_led_encendido_t* this)
{
	return this->flag_timer_led;
}

static int activado_off (fsm_led_encendido_t* this)
{
	return !this->activado;
}

//FUNCIONES DE GUARDA
static void led_activado (fsm_led_encendido_t* this)
{
  __HAL_TIM_SET_COUNTER(this->timer_led, 0); //Reinicio a cero del temporizador del LED
  HAL_TIM_Base_Start_IT(this->timer_led); //Temporizador LED
}

static void led_toggle (fsm_led_encendido_t* this)
{
  HAL_GPIO_TogglePin(this->puerto, this->pin);
  this->timer_led = 0;
  __HAL_TIM_SET_COUNTER(this->timer_led, 0); //Reinicio a cero del temporizador del LED
}

static void led_desactivado (fsm_led_encendido_t* this)
{
  HAL_TIM_Base_Stop_IT(this->timer_led); //Temporizador LED
  this->timer_led = 0;
  HAL_GPIO_WritePin(this->puerto, this->pin, 0);
}
