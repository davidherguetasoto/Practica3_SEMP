/*
 * fsm_led_encendido.h
 *
 *  Created on: Dec 15, 2022
 *      Author: andre
 */

#ifndef INC_FSM_LED_ENCENDIDO_H_
#define INC_FSM_LED_ENCENDIDO_H_

#include "fsm.h"
#include <stdint.h>

typedef void (*start_timer_p)(void*);
typedef void (*stop_timer_p)(void*);
typedef void (*set_timer_p)(void*, int);
typedef void (*toggle_pin_p)(void*);
typedef void (*write_pin_p)(void*, int);

typedef struct{
	fsm_t f;
	void* puerto; //Puerto del LED
	volatile uint8_t* flag_timer_led; //Flag para el timer del LED
	volatile uint8_t* activado; //Variable compartida para señalar que el sistema está activo
	void* timer_led; //Manejador timer del LED
	void* pin;	     //Pin en el que se encuentre el LED

	//Metodos virtuales
	start_timer_p start_timer; //Método para lanzar la cuenta del temporizador
	stop_timer_p stop_timer; //Método para parar la cuenta del temporizador
	set_timer_p set_timer; //Método para colocar un valor en la cuenta del temporizador
	toggle_pin_p toggle_pin; //Método para hacer toggle de un pin
	write_pin_p write_pin; //Método para escribir en un pin

} fsm_led_encendido_t;

fsm_led_encendido_t* _fsm_led_encendido_new (uint8_t* activado, uint8_t* flag_timer_led, void* pin, void* timer_led,
		start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, toggle_pin_p toggle_pin, write_pin_p write_pin); //Constructor de la FSM. Habrá que pasarle el esquema de la FSM y los argumentos de la máquina
void _fsm_led_encendido_init (fsm_led_encendido_t* this, uint8_t* activado, uint8_t* flag_timer_led, void* pin, void* timer_led,
		start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, toggle_pin_p toggle_pin, write_pin_p write_pin);
void _fsm_fire_led_encendido (fsm_led_encendido_t* this);

#endif /* INC_FSM_LED_ENCENDIDO_H_ */
