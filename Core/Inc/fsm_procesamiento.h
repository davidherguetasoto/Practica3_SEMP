/*
 * fsm_procesamiento.h
 *
 *  Created on: 17 dic. 2022
 *      Author: David
 */

#ifndef INC_FSM_PROCESAMIENTO_H_
#define INC_FSM_PROCESAMIENTO_H_

#include "fsm.h"
#include <stdint.h>


typedef void (*pullFIFO_p) (int16_t**);
typedef void (*salida_normal_p)(void*);
typedef void (*salida_high_p)(void*);
typedef void (*salida_extreme_p)(void*);
typedef void (*salida_off_p)(void*);
typedef float (*modulo_p)(int16_t*); //Funcion que calcule el modulo de un vector

typedef struct{
	fsm_t *f;
	volatile uint8_t *activado;
	volatile uint8_t *FIFO_empty;
	void* salida; //Puntero para la estructura de los parámetros de la salida

	//Métodos virtuales
	salida_normal_p salida_normal;
	salida_high_p salida_high;
	salida_extreme_p salida_extreme;
	pullFIFO_p pull_FIFO;
	salida_off_p salida_off;
	modulo_p modulo;
}fsm_procesamiento_t;

fsm_procesamiento_t* _fsm_procesamiento_new(uint8_t* activado, uint8_t* FIFO_empty, void* salida,
		salida_normal_p salida_normal, salida_high_p salida_high, salida_extreme_p salida_extreme,
		pullFIFO_p pull_FIFO, salida_off_p salida_off, modulo_p modulo);
void _fsm_procesamiento_init(fsm_procesamiento_t * this, uint8_t* activado, uint8_t* FIFO_empty, void* salida,
		salida_normal_p salida_normal, salida_high_p salida_high, salida_extreme_p salida_extreme,
		pullFIFO_p pull_FIFO, salida_off_p salida_off, modulo_p modulo);
void _fsm_procesamiento_fire(fsm_procesamiento_t* this);

#endif /* INC_FSM_PROCESAMIENTO_H_ */
