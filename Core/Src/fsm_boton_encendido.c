/*
 * fsm_boton_encendido.c
 *
 *  Created on: 14 dic. 2022
 *      Author: David
 */

#include "fsm_boton_encendido.h"
#include<stdlib.h>



//ESTADOS
enum start_state {
	OFF,
	BOTON_PULSADO,
	ON
};


//FUNCIONES DE TRANSICION
static int boton_presionado (fsm_boton_encendido_t* this);
static int desbloqueo_on (fsm_boton_encendido_t* this);
static int desbloqueo_off (fsm_boton_encendido_t* this);

//FUNCIONES GUARDA
static void inicio_activado (fsm_boton_encendido_t* this);
static void inicio_actualizacion (fsm_boton_encendido_t* this);
static void inicio_desactivado (fsm_boton_encendido_t* this);


//EVOLUCIÓN FSM
static fsm_trans_t inicio[] = {
  { OFF, (fsm_input_func_t)boton_presionado, BOTON_PULSADO, (fsm_output_func_t)inicio_activado},
  { BOTON_PULSADO, (fsm_input_func_t)desbloqueo_on, ON, (fsm_output_func_t)inicio_actualizacion},
  { ON, (fsm_input_func_t)boton_presionado, BOTON_PULSADO,  (fsm_output_func_t)inicio_desactivado },
  { BOTON_PULSADO, (fsm_input_func_t)desbloqueo_off, OFF, (fsm_output_func_t)inicio_actualizacion },
  {-1, NULL, -1, NULL },
  };



fsm_boton_encendido_t* _fsm_boton_encendido_new (uint8_t* activado, uint8_t* flag_timer_boton, void* boton, void* timer_boton,
		boton_pulsado_p boton_pulsado, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer)
{
	fsm_boton_encendido_t* this = (fsm_boton_encendido_t*) malloc (sizeof (fsm_boton_encendido_t));
	_fsm_boton_encendido_init(this,activado,flag_timer_boton,boton, timer_boton,boton_pulsado,start_timer,stop_timer,set_timer);
	return this;
}

void _fsm_boton_encendido_init (fsm_boton_encendido_t* this,uint8_t* activado, uint8_t* flag_timer_boton, void* boton, void* timer_boton,
		boton_pulsado_p boton_pulsado, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer)
{
	fsm_init((fsm_t*)this, inicio);
	this->flag_timer_boton = flag_timer_boton;
	this ->activado = activado;
	this ->boton = boton;
	this ->timer_boton = timer_boton;
	this ->boton_pulsado = boton_pulsado;
	this -> start_timer = start_timer;
	this -> stop_timer = stop_timer;
	this -> set_timer = set_timer;
}

void _fsm_fire_boton_encendido (fsm_boton_encendido_t* this)
{
	fsm_fire((fsm_t*)this);
}

//FUNCIONES DE TRANSICION
static int boton_presionado (fsm_boton_encendido_t* this)
{
	if (this->boton_pulsado(this->boton))
		return 1;
	else
		return 0;
}

static int desbloqueo_on (fsm_boton_encendido_t* this)
{
	if (*(this->flag_timer_boton) && *(this->activado) && !(this->boton_pulsado(this->boton)))
		return 1;
	else
		return 0;
}

static int desbloqueo_off (fsm_boton_encendido_t* this)
{
	if (*(this->flag_timer_boton) && !(*(this->activado)) && !(this->boton_pulsado(this->boton)))
		return 1;
	else
		return 0;
}

//FUNCIONES GUARDA
static void inicio_activado (fsm_boton_encendido_t* this)
{
	*(this -> activado) = 1;
	this -> set_timer(this -> timer_boton, 0); //Reinicio a cero del temporizador del boton
	this -> start_timer(this -> timer_boton); //Temporizador boton start
}

static void inicio_actualizacion (fsm_boton_encendido_t* this)
{
	  this -> stop_timer(this -> timer_boton); //Temporizador boton stop
	  *(this->flag_timer_boton) = 0; //Reinicio del flag del temporizador
}

static void inicio_desactivado (fsm_boton_encendido_t* this)
{
	  *(this->activado) = 0;
	  this -> set_timer(this -> timer_boton, 0); //Reinicio a cero del temporizador del boton
	  this -> start_timer(this -> timer_boton); //Temporizador boton start
}

