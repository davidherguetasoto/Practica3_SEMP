/*
 * fsm_boton_encendido.h
 *
 *  Created on: 14 dic. 2022
 *      Author: David
 */
#ifndef FSM_BOTON_ENCENDIDO_H
#define FSM_BOTON_ENCENDIDO_H

#include "fsm.h"

typedef struct{
	fsm_t* fsm_boton_encendido;

} fsm_boton_encendido_t;

fsm_boton_encendido_t* fsm_boton_encendido_new (fsm_trans_t* tt); //Constructor de la FSM. Habrá que pasarle el esquema de la FSM y los argumentos de la máquina
void fsm_boton_encendido_init (void);
//void fsm_fire_boton_encendido (fsm_t* this);


//FUNCIONES DE TRANSICION
static int boton_presionado (fsm_t* this);
static int desbloqueo_on (fsm_t* this);
static int desbloqueo_off (fsm_t* this);

//FUNCIONES GUARDA
static void inicio_activado (fsm_t* this);
static void inicio_actualizacion (fsm_t* this);
static void inicio_desactivado (fsm_t* this);



//ESTADOS
enum start_state {
	OFF,
	BOTON_PULSADO,
	ON
};

//EVOLUCIÓN FSM
static fsm_trans_t inicio[] = {
  { OFF, boton_presionado, BOTON_PULSADO, inicio_activado},
  { BOTON_PULSADO, desbloqueo_on, ON, inicio_actualizacion},
  { ON, boton_presionado, BOTON_PULSADO,  inicio_desactivado },
  { BOTON_PULSADO, desbloqueo_off, OFF, inicio_actualizacion },
  {-1, NULL, -1, NULL },
  };


#endif
