/*
 * task_fsm.c
 *
 *  Created on: 18 dic. 2022
 *      Author: David
 */
#include "task_fsm.h"


void task_fsm_boton_encendido(void *argument)
{
	task_fsm_boton_encendido_t* p = (task_fsm_boton_encendido_t*)argument;
	while(1)
	{
		osDelay(p->delay);
		fsm_boton_encendido_fire(p->f);
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
