/*
 * task_fsm.c
 *
 *  Created on: 18 dic. 2022
 *      Author: David
 */
#include "task_fsm.h"
#include "main.h"
#include "queue.h"


#define SIZE_FIFO 20
uint8_t fifo_full=0, fifo_empty=1;
QueueHandle_t FIFO=NULL;

void pushFIFO(int16_t** buffer)
{
	xQueueSend(FIFO,buffer,portMAX_DELAY);
	if(uxQueueSpacesAvailable(FIFO)==0)
	{
		fifo_full=1;
	}
	else
	{
		fifo_full=0;
	}
}

void pullFIFO(int16_t** buffer)
{
	xQueueReceive(FIFO,buffer,portMAX_DELAY);
	if(uxQueueMessagesWaiting(FIFO)==0)
	{
		fifo_empty=1;
	}
	else
	{
		fifo_empty=0;
	}
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
		fsm_procesamiento_fire(p->f);
	}
}

void task_fsm_led_encendido(void *argument)
{
	task_fsm_led_encendido_t* p = (task_fsm_led_encendido_t*)argument;
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
	task_fsm_muestreo_t* p = (task_fsm_muestreo_t*)argument;
	/*SI LA FIFO NO ESTÁ CREADA, CREARLA*/
	if(FIFO==NULL)
	{
		FIFO=xQueueCreate(SIZE_FIFO,sizeof(int16_t**));
	}
	p->f = fsm_muestreo_new(p->activado,p->flag_timer_muestreo,p->timer_muestreo,&fifo_full,pushFIFO);
	if (osThreadNew(task_fsm_muestreo, p, (osThreadAttr_t*)p) == NULL) {
		Error_Handler();
	}
}

void task_fsm_procesamiento_create(void *argument)
{
	task_fsm_procesamiento_t* p = (task_fsm_procesamiento_t*)argument;
	/*SI LA FIFO NO ESTÁ CREADA, CREARLA*/
	if(FIFO==NULL)
	{
		FIFO=xQueueCreate(SIZE_FIFO,sizeof(int16_t**));
	}
	p->f = fsm_procesamiento_new(p->activado,p->timer_pwm_salida,p->canal_timer_pwm,&fifo_empty,pullFIFO);
	if (osThreadNew(task_fsm_procesamiento, p, (osThreadAttr_t*)p) == NULL) {
		Error_Handler();
	}
}

void task_fsm_led_encendido_create(void *argument)
{
	task_fsm_led_encendido_t* p = (task_fsm_led_encendido_t*)argument;
	p->f = fsm_led_encendido_new(p->activado,p->flag_timer_led,p->GPIOx_led,p->GPIO_Pin_led,p->timer_led);
	if (osThreadNew(task_fsm_led_encendido,p, (osThreadAttr_t*)p) == NULL) {
	  Error_Handler();
	}
}
