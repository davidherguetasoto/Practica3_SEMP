/*
 * fsm_boton_encendido.c
 *
 *  Created on: 14 dic. 2022
 *      Author: David
 */

#include "fsm_boton_encendido.h"

fsm_boton_encendido_t* fsm_boton_encendido_new (fsm_trans_t* tt /*...*/)
{
	fsm_boton_encendido_t* this = (fsm_boton_encendido_t*) malloc (sizeof (fsm_boton_encendido_t));
	this->fsm_boton_encendido = fsm_new(tt);
	fsm_boton_encendido_init();
	return this;
}

void fsm_boton_encendido_init (void)
{
	//fsm_init(this->fsm_boton_encendido,tt);
	/*...*/
}

/*void fsm_fire_boton_encendido (fsm_t* this)
{

}*/

//FUNCIONES DE TRANSICION
static int boton_presionado (fsm_t* this)
{

}

static int desbloqueo_on (fsm_t* this)
{

}

static int desbloqueo_off (fsm_t* this)
{

}

//FUNCIONES GUARDA
static void inicio_activado (fsm_t* this)
{

}

static void inicio_actualizacion (fsm_t* this)
{

}

static void inicio_desactivado (fsm_t* this)
{

}
