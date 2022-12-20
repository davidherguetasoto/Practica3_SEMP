/*
 * fsm_led_encendido.c
 *
 *  Created on: Dec 15, 2022
 *      Author: andre
 */

#include "fsm_led_encendido.h"
#include <stdlib.h>

//ESTADOS
enum led_state {
	LED_OFF,
	LED_ON
};

//FUNCIONES DE TRANSICION
static int activado_on (fsm_led_encendido_t* this);
static int led_actualizacion (fsm_led_encendido_t* this);
static int activado_off (fsm_led_encendido_t* this);

//FUNCIONES GUARDA
static void led_activado (fsm_led_encendido_t* this);
static void led_toggle (fsm_led_encendido_t* this);
static void led_desactivado (fsm_led_encendido_t* this);

//EVOLUCIÓN FSM
static fsm_trans_t led[] = {
  { LED_OFF, (fsm_input_func_t)activado_on, LED_ON, (fsm_output_func_t)led_activado},
  { LED_ON, (fsm_input_func_t)led_actualizacion, LED_ON, (fsm_output_func_t)led_toggle},
  { LED_ON, (fsm_input_func_t)activado_off, LED_OFF, (fsm_output_func_t)led_desactivado},
  {-1, NULL , -1, NULL },
  };

fsm_led_encendido_t* _fsm_led_encendido_new (uint8_t* activado, uint8_t* flag_timer_led, void* pin, void* timer_led,
		start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, toggle_pin_p toggle_pin, write_pin_p write_pin)
{
	fsm_led_encendido_t* this = (fsm_led_encendido_t*) malloc (sizeof (fsm_led_encendido_t));
	this->f = fsm_new(led);
	_fsm_led_encendido_init(this, activado, flag_timer_led, pin, timer_led, start_timer, stop_timer, set_timer, toggle_pin, write_pin);
	return this;
}

void _fsm_led_encendido_init (fsm_led_encendido_t* this, uint8_t* activado, uint8_t* flag_timer_led, void* pin, void* timer_led,
		start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, toggle_pin_p toggle_pin, write_pin_p write_pin)
{
	this->flag_timer_led = flag_timer_led;
	this->activado = activado;
	this->pin = pin;
	this->timer_led = timer_led;
	this->start_timer = start_timer;
	this->stop_timer = stop_timer;
	this->set_timer = set_timer;
	this->toggle_pin = toggle_pin;
	this->write_pin = write_pin;
}

void _fsm_fire_led_encendido (fsm_led_encendido_t* this)
{
	fsm_fire(this->f);
}

//FUNCIONES DE TRANSICION
static int activado_on (fsm_led_encendido_t* this)
{
	return *this->activado;
}

static int led_actualizacion (fsm_led_encendido_t* this)
{
	return *this->flag_timer_led;
}

static int activado_off (fsm_led_encendido_t* this)
{
	return !(*this->activado);
}

//FUNCIONES DE GUARDA
static void led_activado (fsm_led_encendido_t* this)
{
	this->set_timer(this->timer_led, 0);
	this->start_timer(this->timer_led);
}

static void led_toggle (fsm_led_encendido_t* this)
{
	this->toggle_pin(this->pin);
	this->flag_timer_led = 0;
	this->set_timer(this->timer_led, 0);
}

static void led_desactivado (fsm_led_encendido_t* this)
{
	this->stop_timer(this->timer_led);
	this->flag_timer_led = 0;
	this->write_pin(this->pin, 0);
}

