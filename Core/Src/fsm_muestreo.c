/*
 * fsm_muestreo.c
 *
 *  Created on: 16 dic. 2022
 *      Author: David
 */

#include <stdlib.h>
#include "fsm_muestreo.h"

uint8_t muestra=0;  //Contador de las muestras tomadas
int16_t **buffer_lectura; //buffer para almacenar los datos leidos

//ESTADOS
enum muestreo_state {
	STOP,
	MUESTREO
};

//FUENCIONES DE TRANSICION
static int fsmActivada(fsm_muestreo_t* this);
static int fsmDesactivada(fsm_muestreo_t* this);
static int llegaNuevaLectura(fsm_muestreo_t* this);
static int finLectura(fsm_muestreo_t* this);

//FUNCIONES DE GUARDA
static void activarMuestreo(fsm_muestreo_t* this);
static void desactivarMuestreo(fsm_muestreo_t* this);
static void hacerLectura(fsm_muestreo_t* this);
static void mandar_a_FIFO(fsm_muestreo_t* this);

//EVOLUCION FSM
static fsm_trans_t fsm_muestreo_tt[]={
		{STOP, (fsm_input_func_t)fsmActivada,MUESTREO,(fsm_output_func_t)activarMuestreo},
		{MUESTREO,(fsm_input_func_t)fsmDesactivada, STOP, (fsm_output_func_t)desactivarMuestreo},
		{MUESTREO,(fsm_input_func_t)llegaNuevaLectura,MUESTREO,(fsm_output_func_t)hacerLectura},
		{MUESTREO,(fsm_input_func_t)finLectura,MUESTREO,(fsm_output_func_t)mandar_a_FIFO},
		{-1, NULL, -1, NULL},
};


fsm_muestreo_t* _fsm_muestreo_new(uint8_t* activado, uint8_t* flag_timer_muestreo,
		void* timer, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, uint8_t* FIFO_full, pushFIFO_p pushFIFO,
		lectura_sensor_p lectura_sensor, init_sensor_p init_sensor)
{
	fsm_muestreo_t* this = (fsm_muestreo_t*) malloc (sizeof (fsm_muestreo_t));
	_fsm_muestreo_init (this, activado, flag_timer_muestreo,timer,start_timer,stop_timer,set_timer,FIFO_full,pushFIFO,lectura_sensor,init_sensor);
	return this;
}

void _fsm_muestreo_init(fsm_muestreo_t* this, uint8_t* activado, uint8_t* flag_timer_muestreo,
		void* timer, start_timer_p start_timer, stop_timer_p stop_timer, set_timer_p set_timer, uint8_t* FIFO_full, pushFIFO_p pushFIFO,
		lectura_sensor_p lectura_sensor, init_sensor_p init_sensor)
{
	fsm_init((fsm_t*)this, fsm_muestreo_tt);
	this -> activado = activado;
	this -> flag_timer_muestreo = flag_timer_muestreo;
	this -> FIFO_full = FIFO_full;
	this -> timer = timer;
	this -> start_timer = start_timer;
	this -> stop_timer = stop_timer;
	this -> set_timer = set_timer;
	this -> pushFIFO = pushFIFO;
	this -> lectura_sensor = lectura_sensor;
	this -> init_sensor = init_sensor;
}

void _fsm_muestreo_fire(fsm_muestreo_t* this)
{
	fsm_fire((fsm_t*)this);
}

//FUNCIONES DE TRANSICION
static int fsmActivada(fsm_muestreo_t* this)
{
	if(*(this->activado))
		return 1;
	else
		return 0;
}

static int fsmDesactivada(fsm_muestreo_t* this)
{
	if (!(*(this -> activado)))
		return 1;
	else
		return 0;
}

static int llegaNuevaLectura(fsm_muestreo_t* this)
{
	if((*(this->activado)) && (*(this->flag_timer_muestreo)) && muestra<N_MUESTRAS)
		return 1;
	else
		return 0;
}

static int finLectura(fsm_muestreo_t* this)
{
	if((*(this->activado)) && muestra>=N_MUESTRAS && !(*(this->FIFO_full)))
		return 1;
	else
		return 0;
}


//FUNCIONES GUARDA
static void activarMuestreo(fsm_muestreo_t* this)
{
	muestra=0;
	buffer_lectura = malloc(N_EJES * sizeof(int16_t*));
	for (int i = 0; i < N_EJES; ++i) {
	    buffer_lectura[i] = malloc(N_MUESTRAS * sizeof(int16_t));
	}
	*(this->flag_timer_muestreo)=0;
	this->set_timer(this->timer,0);
	this->start_timer(this->timer);
	this->init_sensor();
}

static void desactivarMuestreo(fsm_muestreo_t* this)
{
	this -> stop_timer(this->timer);
	*(this->flag_timer_muestreo)=0;
	for (int i = 0; i < N_EJES; ++i) {
		free(buffer_lectura[i]);
	}
	free(buffer_lectura);
}

static void hacerLectura(fsm_muestreo_t* this)
{
	int16_t* sensor = malloc(N_EJES*sizeof(int16_t*));
	this->lectura_sensor(sensor);
	buffer_lectura[x][muestra] = sensor[x];
	buffer_lectura[y][muestra] = sensor[y];
	buffer_lectura[z][muestra] = sensor[z];
	free(sensor);
	muestra = muestra + 1;
	*(this->flag_timer_muestreo)=0;
	this -> set_timer(this->timer,0);
}

static void mandar_a_FIFO(fsm_muestreo_t* this)
{
	for (int i = 0; i < N_EJES; i++) {
		for (int j = 0; j < N_MUESTRAS; j++){
			this -> pushFIFO(&buffer_lectura[i][j]);
		}
	}
	*(this->flag_timer_muestreo)=0;
	this -> set_timer(this->timer, 0);
	muestra = 0;
}
