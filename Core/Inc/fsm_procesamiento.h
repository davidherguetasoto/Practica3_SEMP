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

#define N_MUESTRAS 20

typedef void (*pullFIFO_p) (int16_t*);
typedef void (*salida_normal_p)(void*);
typedef void (*salida_high_p)(void*);
typedef void (*salida_extreme_p)(void*);
typedef void (*salida_off_p)(void*);

typedef struct{
	fsm_t *f;
	volatile uint8_t *activado;
	volatile uint8_t FIFO_empty;
	void* salida; //Puntero para la estructura de los parámetros de la salida

	//Métodos virtuales
	salida_normal_p salida_normal;
	salida_high_p salida_high;
	salida_extreme_p salida_extreme;
	pullFIFO_p pull_FIFO;
	salida_off_p salida_off;
}fsm_procesamiento_t;

fsm_procesamiento_t* _fsm_procesamiento_new();
void _fsm_procesamiento_init();
void _fsm_muestreo_fire(fsm_muestreo_t* this);

#endif /* INC_FSM_PROCESAMIENTO_H_ */
