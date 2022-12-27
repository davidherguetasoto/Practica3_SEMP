/*
 * fsm_procesamiento.c
 *
 *  Created on: 17 dic. 2022
 *      Author: David
 */

#include "fsm_procesamiento.h"
#include<stdlib.h>

#define N_muestra_pS 20
#define HIGH 2400
#define EXTREME 3000

//VARIABLES PRIVADAS
uint8_t muestra_p=0;  //Contador de las muestra_ps tomadas
int16_t **buffer_lectura_p; //buffer para almacenar los datos leidos
float *buffer_modulo; //buffer en el que se almaena el módulo de los datos recogidos
float max=0, min=0; //Máximo y mínimo de los módulos

//ESTADOS
enum procesamiento_state{
	ESPERA,
	CALCULAR_MODULO,
	MAX_MIN
};

//FUNCIONES DE TRANSICIÓN
int llegamuestra_p(fsm_procesamiento_t* this);
int fsmDesactivada(fsm_procesamiento_t* this);
int aCalcularModulo(fsm_procesamiento_t* this);
int finModulo(fsm_procesamiento_t* this);
int fsmDesactivada(fsm_procesamiento_t* this);
int aSalidaNormal(fsm_procesamiento_t* this);
int aSalidaHigh(fsm_procesamiento_t* this);
int aSalidaExtreme(fsm_procesamiento_t* this);
int aMax(fsm_procesamiento_t* this);
int aMin(fsm_procesamiento_t* this);
int aSiguiente(fsm_procesamiento_t* this);

//FUNCIONES GUARDA
void preparacionCalculo(fsm_procesamiento_t* this);
void calculoModulo(fsm_procesamiento_t* this);
void preparacionMaxMin(fsm_procesamiento_t* this);
void salidaOFF(fsm_procesamiento_t* this);
void salidaNormal(fsm_procesamiento_t* this);
void salidaHigh(fsm_procesamiento_t* this);
void salidaExtreme(fsm_procesamiento_t* this);
void nuevoMax(fsm_procesamiento_t* this);
void nuevoMin(fsm_procesamiento_t* this);
void siguientemuestra_p(fsm_procesamiento_t* this);

//EVOLUCIÓN FSM
static fsm_trans_t fsm_procesamiento_tt[]={
		{ESPERA,(fsm_input_func_t)llegamuestra_p,CALCULAR_MODULO,(fsm_output_func_t)preparacionCalculo},
		{CALCULAR_MODULO,(fsm_input_func_t)fsmDesactivada,ESPERA,(fsm_output_func_t)salidaOFF},
		{CALCULAR_MODULO,(fsm_input_func_t)aCalcularModulo,CALCULAR_MODULO,(fsm_output_func_t)calculoModulo},
		{CALCULAR_MODULO,(fsm_input_func_t)finModulo,MAX_MIN,(fsm_output_func_t)preparacionMaxMin},
		{MAX_MIN,(fsm_input_func_t)fsmDesactivada,ESPERA,(fsm_output_func_t)salidaOFF},
		{MAX_MIN,(fsm_input_func_t)aSalidaNormal,ESPERA,(fsm_output_func_t)salidaNormal},
		{MAX_MIN,(fsm_input_func_t)aSalidaHigh,ESPERA,(fsm_output_func_t)salidaHigh},
		{MAX_MIN,(fsm_input_func_t)aSalidaExtreme,ESPERA,(fsm_output_func_t)salidaExtreme},
		{MAX_MIN,(fsm_input_func_t)aMax,MAX_MIN,(fsm_output_func_t)nuevoMax},
		{MAX_MIN,(fsm_input_func_t)aMin,MAX_MIN,(fsm_output_func_t)nuevoMin},
		{MAX_MIN,(fsm_input_func_t)aSiguiente,MAX_MIN,(fsm_output_func_t)siguientemuestra_p},
		{-1, NULL, -1, NULL},
};


fsm_procesamiento_t* _fsm_procesamiento_new(uint8_t* activado, uint8_t* FIFO_empty, void* salida,
		salida_normal_p salida_normal, salida_high_p salida_high, salida_extreme_p salida_extreme,
		pullFIFO_p pull_FIFO, salida_off_p salida_off, modulo_p modulo)
{
	fsm_procesamiento_t* this = (fsm_procesamiento_t*)malloc(sizeof(fsm_procesamiento_t));
	_fsm_procesamiento_init(this,activado,FIFO_empty,salida,salida_normal,salida_high,salida_extreme,pull_FIFO,salida_off,modulo);
	return this;
}

void _fsm_procesamiento_init(fsm_procesamiento_t * this, uint8_t* activado, uint8_t* FIFO_empty, void* salida,
		salida_normal_p salida_normal, salida_high_p salida_high, salida_extreme_p salida_extreme,
		pullFIFO_p pull_FIFO, salida_off_p salida_off, modulo_p modulo)
{
	fsm_init((fsm_t*)this, fsm_procesamiento_tt);
	this -> activado = activado;
	this -> FIFO_empty = FIFO_empty;
	this -> salida = salida;
	this -> salida_normal = salida_normal;
	this -> salida_high = salida_high;
	this -> salida_extreme = salida_extreme;
	this -> salida_off = salida_off;
	this -> modulo = modulo;
}

void _fsm_procesamiento_fire(fsm_procesamiento_t* this)
{
	fsm_fire((fsm_t*)this);
}

//FUNCIONES DE TRANSICIÓN
int llegamuestra_p(fsm_procesamiento_t* this)
{
	if(*(this->activado)&& !(*(this->FIFO_empty)))
		return 1;
	else
		return 0;
}

int fsmDesactivada(fsm_procesamiento_t* this)
{
	if(!(*(this->activado)))
		return 1;
	else
		return 0;
}

int aCalcularModulo(fsm_procesamiento_t* this)
{
	if(*(this->activado) && muestra_p<N_muestra_pS)
		return 1;
	else
		return 0;
}

int finModulo(fsm_procesamiento_t* this)
{
	if(*(this->activado)&& muestra_p>=N_muestra_pS)
		return 1;
	else
		return 0;
}

int aSalidaNormal(fsm_procesamiento_t* this)
{
	if(*(this->activado) && muestra_p>=N_muestra_pS && (max-min)<HIGH)
		return 1;
	else
		return 0;
}

int aSalidaHigh(fsm_procesamiento_t* this)
{
	if(*(this->activado) && muestra_p>=N_muestra_pS && (max-min)>=HIGH && (max-min)<EXTREME)
		return 1;
	else
		return 0;
}

int aSalidaExtreme(fsm_procesamiento_t* this)
{
	if(*(this->activado) && muestra_p>=N_muestra_pS && (max-min)>=EXTREME)
		return 1;
	else
		return 0;
}

int aMax(fsm_procesamiento_t* this)
{
	if(*(this->activado) && muestra_p<N_muestra_pS && buffer_modulo[muestra_p]>max)
		return 1;
	else
		return 0;
}

int aMin(fsm_procesamiento_t* this)
{
	if(*(this->activado) && muestra_p<N_muestra_pS && buffer_modulo[muestra_p]<min)
		return 1;
	else
		return 0;
}

int aSiguiente(fsm_procesamiento_t* this)
{
	if(*(this->activado) && muestra_p<N_muestra_pS && buffer_modulo[muestra_p]<=max && buffer_modulo[muestra_p]>=min)
		return 1;
	else
		return 0;
}

//FUNCIONES GUARDA
void preparacionCalculo(fsm_procesamiento_t* this)
{
	buffer_modulo = (float*)malloc(N_muestra_pS*sizeof(float));
	this->pull_FIFO(buffer_lectura_p);
	muestra_p = 0;
}

void calculoModulo(fsm_procesamiento_t* this)
{
	buffer_modulo[muestra_p]=this->modulo(buffer_lectura_p[muestra_p]);
	muestra_p = muestra_p + 1;
}

void preparacionMaxMin(fsm_procesamiento_t* this)
{
	muestra_p = 0;
	min = buffer_modulo[0];
	max = buffer_modulo[0];
}

void salidaOFF(fsm_procesamiento_t* this)
{
	this -> salida_off(this->salida);
	free(buffer_modulo);
}

void salidaNormal(fsm_procesamiento_t* this)
{
	this -> salida_normal(this->salida);
	free(buffer_modulo);
}
void salidaHigh(fsm_procesamiento_t* this)
{
	this -> salida_high(this->salida);
	free(buffer_modulo);
}

void salidaExtreme(fsm_procesamiento_t* this)
{
	this -> salida_extreme(this->salida);
	free(buffer_modulo);
}

void nuevoMax(fsm_procesamiento_t* this)
{
	max = buffer_modulo[muestra_p];
	muestra_p = muestra_p + 1;
}

void nuevoMin(fsm_procesamiento_t* this)
{
	min = buffer_modulo[muestra_p];
	muestra_p = muestra_p + 1;
}

void siguientemuestra_p(fsm_procesamiento_t* this)
{
	muestra_p = muestra_p + 1;
}

