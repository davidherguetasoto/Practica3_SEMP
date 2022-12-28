/*
 * fsm_muestreo.h
 *
 *  Created on: 16 dic. 2022
 *      Author: David
 */

#ifndef INC_FSM_MUESTREO_H_
#define INC_FSM_MUESTREO_H_

#include "fsm.h"
#include <stdint.h>


#define N_MUESTRAS 20
#define N_EJES 3

enum ejes{
	x,
	y,
	z
};

typedef void (*start_timer_p)(void*);
typedef void (*stop_timer_p)(void*);
typedef void (*set_timer_p)(void*, int);
typedef void (*pushFIFO_p)(int16_t*);
typedef void (*lectura_sensor_p)(int16_t*);
typedef void (*init_sensor_p)(void);

typedef struct {
	fsm_t f;
	volatile uint8_t *activado;
	volatile uint8_t *flag_timer_muestreo;
	volatile uint8_t *FIFO_full;
	void *timer;

	//Métodos virtuales
	start_timer_p start_timer;
	stop_timer_p stop_timer;
	set_timer_p set_timer;
	pushFIFO_p pushFIFO;
	lectura_sensor_p lectura_sensor;
	init_sensor_p init_sensor;
}fsm_muestreo_t;

fsm_muestreo_t* _fsm_muestreo_new(uint8_t* activado, uint8_t* flag_timer_muestreo,
		void* timer, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, uint8_t* FIFO_full, pushFIFO_p pushFIFO,
		lectura_sensor_p lectura_sensor, init_sensor_p init_sensor);
void _fsm_muestreo_init(fsm_muestreo_t* this, uint8_t* activado, uint8_t* flag_timer_muestreo,
		void* timer, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, uint8_t* FIFO_full, pushFIFO_p pushFIFO,
		lectura_sensor_p lectura_sensor, init_sensor_p init_sensor);
void _fsm_muestreo_fire(fsm_muestreo_t* this);


#endif /* INC_FSM_MUESTREO_H_ */
