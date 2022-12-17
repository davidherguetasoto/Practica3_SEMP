/*
 * fsm_procesamiento.c
 *
 *  Created on: 17 dic. 2022
 *      Author: David
 */


#include "fsm_procesamiento.h"
#include<math.h>
#include<stdlib.h>

//VARIABLES PRIVADAS
uint8_t muestra=0;  //Contador de las muestras tomadas
int16_t *buffer_lectura; //buffer para almacenar los datos leidos
float *buffer_modulo; //buffer en el que se almaena el módulo de los datos recogidos
float max, min; //Máximo y mínimo de los módulos

//ESTADOS
enum procesamiento_state{
	ESPERA,
	CALCULAR_MODULO,
	MAX_MIN
};

//FUNCIONES DE TRANSICIÓN
int llegaMuestra(fsm_procesamiento_t* this);
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
void desactivarCalculo(fsm_procesamiento_t* this);
void calculoModulo(fsm_procesamiento_t* this);
void preparacionMaxMin(fsm_procesamiento_t* this);
void salidaOFF(fsm_procesamiento_t* this);
void salidaNormal(fsm_procesamiento_t* this);
void salidaHigh(fsm_procesamiento_t* this);
void salidaExtreme(fsm_procesamiento_t* this);
void nuevoMax(fsm_procesamiento_t* this);
void nuevoMin(fsm_procesamiento_t* this);
void siguienteMuestra(fsm_procesamiento_t* this);

//EVOLUCIÓN FSM
static fsm_trans_t fsm_procesamiento_tt[]={
		{ESPERA,(fsm_input_func_t)llegaMuestra,CALCULAR_MODULO,(fsm_output_func_t)preparacionCalculo},
		{CALCULAR_MODULO,(fsm_input_func_t)fsmDesactivada,ESPERA,(fsm_output_func_t)desactivarCalculo},
		{CALCULAR_MODULO,(fsm_input_func_t)aCalcularModulo,CALCULAR_MODULO,(fsm_output_func_t)calculoModulo},
		{CALCULAR_MODULO,(fsm_input_func_t)finModulo,MAX_MIN,(fsm_output_func_t)preparacionMaxMin},
		{MAX_MIN,(fsm_input_func_t)fsmDesactivada,ESPERA,(fsm_output_func_t)salidaOFF},
		{MAX_MIN,(fsm_input_func_t)aSalidaNormal,ESPERA,(fsm_output_func_t)salidaNormal},
		{MAX_MIN,(fsm_input_func_t)aSalidaHigh,ESPERA,(fsm_output_func_t)salidaHigh},
		{MAX_MIN,(fsm_input_func_t)aSalidaExtreme,ESPERA,(fsm_output_func_t)salidaExtreme},
		{MAX_MIN,(fsm_input_func_t)aMax,MAX_MIN,(fsm_output_func_t)nuevoMax},
		{MAX_MIN,(fsm_input_func_t)aMin,MAX_MIN,(fsm_output_func_t)nuevoMin},
		{MAX_MIN,(fsm_input_func_t)aSiguiente,MAX_MIN,(fsm_output_func_t)siguienteMuestra},
		{-1, NULL, -1, NULL},
};


fsm_procesamiento_t* _fsm_procesamiento_new()
{

}

void _fsm_procesamiento_init()
{

}

void _fsm_muestreo_fire(fsm_muestreo_t* this)
{

}

float modulo(float* buffer)
{
	return sqrt(buffer[muestra][0]*buffer[muestra][0]+buffer[muestra][1]*buffer[muestra][1]+buffer[muestra][2]*buffer[muestra][2]);
}

//FUNCIONES DE TRANSICIÓN
int llegaMuestra(fsm_procesamiento_t* this)
{

}

int fsmDesactivada(fsm_procesamiento_t* this)
{

}

int aCalcularModulo(fsm_procesamiento_t* this)
{

}

int finModulo(fsm_procesamiento_t* this)
{

}

int fsmDesactivada(fsm_procesamiento_t* this)
{

}

int aSalidaNormal(fsm_procesamiento_t* this)
{

}

int aSalidaHigh(fsm_procesamiento_t* this)
{

}

int aSalidaExtreme(fsm_procesamiento_t* this)
{

}

int aMax(fsm_procesamiento_t* this)
{

}

int aMin(fsm_procesamiento_t* this)
{

}

int aSiguiente(fsm_procesamiento_t* this)
{

}

//FUNCIONES GUARDA
void preparacionCalculo(fsm_procesamiento_t* this)
{

}

void desactivarCalculo(fsm_procesamiento_t* this)
{

}

void calculoModulo(fsm_procesamiento_t* this)
{

}

void preparacionMaxMin(fsm_procesamiento_t* this)
{

}

void salidaOFF(fsm_procesamiento_t* this)
{

}

void salidaNormal(fsm_procesamiento_t* this)
{

}
void salidaHigh(fsm_procesamiento_t* this)
{

}

void salidaExtreme(fsm_procesamiento_t* this)
{

}

void nuevoMax(fsm_procesamiento_t* this)
{

}

void nuevoMin(fsm_procesamiento_t* this)
{

}

void siguienteMuestra(fsm_procesamiento_t* this)
{

}

