/*
 * joystick.c
 *
 *  Created on: 25 mar. 2020
 *      Author: Hristo
 */

#include "joystick.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <signal.h>
#include "../dyn_test/fake_msp.h"
#include "../dyn_test/b_queue.h"
#include "../main/main.h"

uint8_t Estado_actual = Ninguno, Anterior = Ninguno;

void Set_estado_anterior(uint8_t valor){
	Anterior = valor;
}

void Set_estado_actual(uint8_t valor){
	Estado_actual = valor;
}

void Get_estado(uint8_t* estado, uint8_t* anterior ){
	*estado = Estado_actual;
	*anterior = Anterior;
}

/**
 * Handler to exit the current thread under the appropiate signal
 */
static void handler(int signum)
{
	pthread_exit(NULL);
}

/**
 * Thread to emulate the joystick
 */
void* joystick_emu(void *vargp) {
	uint8_t tecla, estado;

	// Add SIGTERM handler to kill the current thread
	signal(SIGTERM, handler);

	while(1){
		scanf("%c", &tecla);

//		printf("Tecla: %c, 0x%02X\n", tecla, tecla);
//		fflush(stdout);
		switch(tecla){
		case 0x0A:
		case 0x0D:
			continue; //omitir el retorno, yendo directamente a la siguiente iteracion del while.
		case 'i':
			estado = Up;
			break;
		case 'j':
			estado = Left;
			break;
		case 'k':
			estado = Center;
			break;
		case 'l':
			estado = Right;
			break;
		case 'm':
			estado = Down;
			break;
		case 'a':
			estado = Sw1;
			break;
		case 's':
			estado = Sw2;
			break;
		case 'q':
			estado = Quit;
			break;
		default:
			estado = Ninguno;
		}
		Anterior = Otro;//Me aseguro de que anterior sea diferente de estado}
		Estado_actual = estado;
//		printf("Estado actual = %d\n", Estado_actual);
//		fflush(stdout);
	}
}

