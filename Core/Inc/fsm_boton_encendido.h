/*
 * fsm_boton_encendido.h
 *
 *  Created on: 14 dic. 2022
 *      Author: David
 */
#ifndef FSM_BOTON_ENCENDIDO_H
#define FSM_BOTON_ENCENDIDO_H

#include "fsm.h"
#include <stdint.h>

typedef int (*boton_pulsado_p)(void*);
typedef void (*start_timer_p)(void*);
typedef void (*stop_timer_p)(void*);
typedef void (*set_timer_p)(void*,int);

typedef struct{
	fsm_t* f;
	volatile uint8_t *flag_timer_boton; //Flag para el timer del boton
	volatile uint8_t *activado; //Variable compartida para señalar que el sistema está activo
	void *timer_boton; //Referencia del temporizador
	void *boton; //Referencia del boton

	//Metodos virtuales
	boton_pulsado_p boton_pulsado; //Método que comprueba si la entrada (botón) está activa
	start_timer_p start_timer; //Método para lanzar la cuenta del temporizador
	stop_timer_p stop_timer; //Método para parar la cuenta del temporizador
	set_timer_p set_timer; //Método para colocar un valor en la cuenta del temporizador

} fsm_boton_encendido_t;

fsm_boton_encendido_t* _fsm_boton_encendido_new (uint8_t* activado, uint8_t* flag_timer_boton, void* boton, void* timer_boton,
		boton_pulsado_p boton_pulsado, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer); //Constructor de la FSM. Habrá que pasarle el esquema de la FSM y los argumentos de la máquina
void _fsm_boton_encendido_init (fsm_boton_encendido_t* this,uint8_t* activado, uint8_t* flag_timer_boton, void* boton, void* timer_boton,
		boton_pulsado_p boton_pulsado, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer);
void _fsm_fire_boton_encendido (fsm_boton_encendido_t* this);


//FUNCIONES DE TRANSICION
static int boton_presionado (fsm_boton_encendido_t* this);
static int desbloqueo_on (fsm_boton_encendido_t* this);
static int desbloqueo_off (fsm_boton_encendido_t* this);

//FUNCIONES GUARDA
static void inicio_activado (fsm_boton_encendido_t* this);
static void inicio_actualizacion (fsm_boton_encendido_t* this);
static void inicio_desactivado (fsm_boton_encendido_t* this);


#endif
