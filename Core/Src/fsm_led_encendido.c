/*
 * fsm_led_encendido.c
 *
 *  Created on: Dec 15, 2022
 *      Author: andre
 */

#include "fsm_led_encendido.h"
#include <stdlib.h>

fsm_led_encendido_t* fsm_led_encendido_new (uint32_t delay, void* port, uint16_t pin, uint8_t flag_timer_led, void* timer_led, uint8_t activado)
{
	fsm_led_encendido_t* this = (fsm_led_encendido_t*) malloc (sizeof (fsm_led_encendido_t));
	this->f = fsm_new(led);
	fsm_led_encendido_init(this, delay, port, pin, flag_timer_led, timer_led, activado);
	return this;
}

void fsm_led_encendido_init (fsm_led_encendido_t* this, uint32_t delay, void* puerto, uint16_t pin, uint8_t flag_timer_led, void* timer_led, uint8_t activado)
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
  start_timer(this->timer_led);
}

static void led_toggle (fsm_led_encendido_t* this)
{
  toggle_pin(this->puerto, this->pin);
  this->timer_led = 0;
  stop_timer(this->timer_led, 0);
}

static void led_desactivado (fsm_led_encendido_t* this)
{
  stop_timer(this->timer_led);
  this->timer_led = 0;
  write_pin(this->puerto, this->pin, 0);
}
