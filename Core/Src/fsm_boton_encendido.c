/*
 * fsm_boton_encendido.c
 *
 *  Created on: 14 dic. 2022
 *      Author: David
 */

#include "fsm_boton_encendido.h"
#include<stdlib.h>

fsm_boton_encendido_t* fsm_boton_encendido_new (uint32_t delay, GPIO_TypeDef* port, uint16_t pin, uint8_t flag_timer_boton, TIM_HandleTypeDef *timer_boton, uint8_t activado)
{
	fsm_boton_encendido_t* this = (fsm_boton_encendido_t*) malloc (sizeof (fsm_boton_encendido_t));
	this->f = fsm_new(inicio);
	fsm_boton_encendido_init(this, delay, port, pin, flag_timer_boton, timer_boton, activado);
	return this;
}

void fsm_boton_encendido_init (fsm_boton_encendido_t* this, uint32_t delay, GPIO_TypeDef* puerto, uint16_t pin, uint8_t flag_timer_boton, TIM_HandleTypeDef* timer_boton, uint8_t activado)
{
	//fsm_init(this->fsm_boton_encendido,tt);
	this->delay = delay;
	this->puerto = puerto;
	this->pin = pin;
	this->flag_timer_boton = flag_timer_boton;
	this ->activado = activado;
	this ->timer_boton = timer_boton;
}

void fsm_fire_boton_encendido (fsm_boton_encendido_t* this)
{
	fsm_fire(this->f);
}

//FUNCIONES DE TRANSICION
static int boton_presionado (fsm_boton_encendido_t* this)
{
	if (HAL_GPIO_ReadPin(this->puerto, this->pin) == 1)
		return 1;
	else
		return 0;
}

static int desbloqueo_on (fsm_boton_encendido_t* this)
{
	if (this->flag_timer_boton && this->activado && (HAL_GPIO_ReadPin(this->puerto, this->pin) == 0))
		return 1;
	else
		return 0;
}

static int desbloqueo_off (fsm_boton_encendido_t* this)
{
	if (this->flag_timer_boton && !this->activado && (HAL_GPIO_ReadPin(this->puerto, this->pin) == 0))
		return 1;
	else
		return 0;
}

//FUNCIONES GUARDA
static void inicio_activado (fsm_boton_encendido_t* this)
{
	this -> activado = 1;
	 __HAL_TIM_SET_COUNTER(this->timer_boton, 0); //Reinicio a cero del temporizador del boton
	 HAL_TIM_Base_Start_IT(this->timer_boton); //Temporizador boton
}

static void inicio_actualizacion (fsm_boton_encendido_t* this)
{
	  HAL_TIM_Base_Stop_IT(this->timer_boton); //Temporizador boton stop
	  this->flag_timer_boton = 0; //Reinicio del flag del temporizador
}

static void inicio_desactivado (fsm_boton_encendido_t* this)
{
	  this->activado = 0;
	  __HAL_TIM_SET_COUNTER(this->timer_boton, 0); //Reinicio a cero del temporizador del boton
	  HAL_TIM_Base_Start_IT(this->timer_boton); //Temporizador boton
}
