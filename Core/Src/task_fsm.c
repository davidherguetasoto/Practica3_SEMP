/*
 * task_fsm.c
 *
 *  Created on: 18 dic. 2022
 *      Author: David
 */
#include "task_fsm.h"

void pushFIFO(int16_t** buffer)
{

}

void pullFIFO(int16_t** buffer)
{

}

void task_fsm_boton_encendido(void *argument)
{
	task_fsm_boton_encendido_t* p = (task_fsm_boton_encendido_t*)argument;
	while(1)
	{
		osDelay(p->delay);
		fsm_boton_encendido_fire(p->f);
	}
}

void task_fsm_muestreo(void *argument)
{
	task_fsm_muestreo_t* p = (task_fsm_muestreo_t*)argument;
	while(1)
	{
		osDelay(p->delay);
		fsm_muestreo_fire(p->f);
	}
}

void task_fsm_procesamiento(void *argument)
{
	task_fsm_procesamiento_t* p = (task_fsm_procesamiento_t*)argument;
	while(1)
	{
		osDelay(p->delay);
		fsm_pocesamiento_fire(p->f);
	}
}

void task_fsm_led_encendido(void *argument)
{
	task_fsm_boton_encendido_t* p = (task_fsm_led_encendido_t*)argument;
	while(1)
	{
		osDelay(p->delay);
		fsm_led_encendido_fire(p->f);
	}
}

void task_fsm_boton_encendido_create(void *argument)
{
	task_fsm_boton_encendido_t* p = (task_fsm_boton_encendido_t*)argument;
	p->f = fsm_boton_encendido_new(p->activado,p->flag_timer_boton,p->port,p->pin,p->timer_boton);
  if (osThreadNew(task_fsm_boton_encendido, p, (osThreadAttr_t*)p) == NULL) {
    Error_Handler();
  }
}

void task_fsm_muestreo_create(void *argument)
{

}

void task_fsm_procesamiento_create(void *argument)
{

}

void task_fsm_led_encendido_create(void *argument)
{

}
