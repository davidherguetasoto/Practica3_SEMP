/*
 * fsm_boton_encendido.h
 *
 *  Created on: 14 dic. 2022
 *      Author: David
 */
#ifndef FSM_BOTON_ENCENDIDO_H
#define FSM_BOTON_ENCENDIDO_H

#include "fsm.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal.h"

typedef struct{
	fsm_t* f;
	uint32_t delay; //Frecuencia de activacion de la FSM
	GPIO_TypeDef * puerto; //Puerto del boton
	uint16_t pin;	     //Pin en el que se encuentre el boton
	volatile uint8_t flag_timer_boton; //Flag para el timer del boton
	uint8_t activado; //Variable compartida para señalar que el sistema está activo
	TIM_HandleTypeDef *timer_boton; //Manejador timer del botón
} fsm_boton_encendido_t;

fsm_boton_encendido_t* fsm_boton_encendido_new (uint32_t delay, GPIO_TypeDef* port, uint16_t pin, uint8_t flag_timer_boton, TIM_HandleTypeDef *timer_boton, uint8_t activado); //Constructor de la FSM. Habrá que pasarle el esquema de la FSM y los argumentos de la máquina
void fsm_boton_encendido_init (fsm_boton_encendido_t* this, uint32_t delay, GPIO_TypeDef* puerto, uint16_t pin, uint8_t flag_timer_boton, TIM_HandleTypeDef* timer_boton, uint8_t activado);
void fsm_fire_boton_encendido (fsm_boton_encendido_t* this);


//FUNCIONES DE TRANSICION
static int boton_presionado (fsm_boton_encendido_t* this);
static int desbloqueo_on (fsm_boton_encendido_t* this);
static int desbloqueo_off (fsm_boton_encendido_t* this);

//FUNCIONES GUARDA
static void inicio_activado (fsm_boton_encendido_t* this);
static void inicio_actualizacion (fsm_boton_encendido_t* this);
static void inicio_desactivado (fsm_boton_encendido_t* this);



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
