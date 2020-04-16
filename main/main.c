#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <semaphore.h> //añadido para que compile
#include <fcntl.h> //añadido para que compile
#include "main.h"
#include "../dyn/dyn_app_common.h"
#include "../dyn_test/dyn_emu.h"
#include "../dyn_test/b_queue.h"
#include "../joystick_emu/joystick.h"

uint8_t estado = Ninguno, estado_anterior = Ninguno, finalizar = 0;
/**
 * main.c
 */
int main(void)
{
	pthread_t tid, jid;
	uint8_t tmp;

	//Init semaphores for TX data handshake
    sem_unlink("/semaphore_tx_msp");
    sem_unlink("/semaphore_tx_cli");
    sem_tx_msp = sem_open("/semaphore_tx_msp",O_CREAT,0644,0);
    sem_tx_cli = sem_open("/semaphore_tx_cli",O_CREAT,0644,0);

	//Init queue for RX data
	init_queue();

	//Start thread for dynamixel module emulation
	pthread_create(&tid, NULL, dyn_emu, (void*) &tid);
	pthread_create(&jid, NULL, joystick_emu, (void*) &jid);

	//Testing some high level function
	printf("MAIN: Setting LED to 0 \n");
    dyn_led_control(1, 0);
    printf("MAIN: Getting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 0);
    printf("MAIN: Setting LED to 1 \n");
	dyn_led_control(1, 1);
	printf("MAIN: Getting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 1);


	printf("************************\n");
	printf("Test passed successfully\n");
	printf("Pulsar 'q' para terminar, qualquier tecla para seguir\r");
	fflush(stdout);//	return 0;

	while(estado != Quit)
	{
		Get_estado(&estado, &estado_anterior);
		if(estado != estado_anterior){
			Set_estado_anterior(estado);
			printf("estado = %d\n", estado);
			fflush(stdout);
			switch(estado){
			case Sw1:
				printf("Boton Sw1 ('a') apretado\n");
				break;
			case Sw2:
				printf("Boton Sw2 ('s') apretado\n");
				break;
			case Quit:
				printf("Adios!\n");
				break;
			//etc, etc...
			}
			fflush(stdout);
		}
	}
	printf("Programa terminado\n");
	//Signal the emulation thread to stop
	pthread_kill(tid, SIGTERM);
	pthread_kill(jid, SIGTERM);
}
