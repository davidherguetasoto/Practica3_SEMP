/*
 * fsm_led_encendido.h
 *
 *  Created on: Dec 15, 2022
 *      Author: andre
 */

#ifndef INC_FSM_LED_ENCENDIDO_H_
#define INC_FSM_LED_ENCENDIDO_H_

#include "fsm.h"
#include "stm32f4xx.h"

typedef struct{
	fsm_t* f;
	uint32_t delay; //Frecuencia de activacion de la FSM
	GPIO_TypeDef * puerto; //Puerto del LED
	uint16_t pin;	     //Pin en el que se encuentre el LED
	volatile uint8_t flag_timer_led; //Flag para el timer del LED
	uint8_t activado; //Variable compartida para señalar que el sistema está activo
	TIM_HandleTypeDef *timer_led; //Manejador timer del LED
} fsm_led_encendido_t;

fsm_led_encendido_t* fsm_led_encendido_new (uint32_t delay, GPIO_TypeDef* port, uint16_t pin, uint8_t flag_timer_led, TIM_HandleTypeDef *timer_led, uint8_t activado); //Constructor de la FSM. Habrá que pasarle el esquema de la FSM y los argumentos de la máquina
void fsm_led_encendido_init (fsm_led_encendido_t* this, uint32_t delay, GPIO_TypeDef* puerto, uint16_t pin, uint8_t flag_timer_led, TIM_HandleTypeDef* timer_led, uint8_t activado);
void fsm_fire_led_encendido (fsm_led_encendido_t* this);

//FUNCIONES DE TRANSICION
static int activado_on (fsm_led_encendido_t* this);
static int led_actualizacion (fsm_led_encendido_t* this);
static int activado_off (fsm_led_encendido_t* this);

//FUNCIONES DE GUARDA
static void led_activado (fsm_led_encendido_t* this);
static void led_toggle (fsm_led_encendido_t* this);
static void led_desactivado (fsm_led_encendido_t* this);

//ESTADOS
enum led_state {
	LED_OFF,
	LED_ON
};

//EVOLUCIÓN FSM
static fsm_trans_t led[] = {
  { LED_OFF, (fsm_t*)activado_on, LED_ON, (fsm_t*)led_activado},
  { LED_ON, (fsm_t*)led_actualizacion, LED_ON, (fsm_t*)led_toggle},
  { LED_ON, (fsm_t*)activado_off, LED_OFF, (fsm_t*)led_desactivado},
  {-1, NULL, -1, NULL },
  };

#endif /* INC_FSM_LED_ENCENDIDO_H_ */
