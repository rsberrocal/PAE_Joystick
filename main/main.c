#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <semaphore.h> //Added to compile
#include <fcntl.h> //Added to compile
#include "main.h"
#include "../dyn/dyn_app_common.h"
#include "../dyn_test/dyn_emu.h"
#include "../dyn_test/b_queue.h"
#include "../joystick_emu/joystick.h"
#include "../dyn/dyn_motors.h"

uint8_t estado = Ninguno, estado_anterior = Ninguno, finalizar = 0;

/**
 * main.c
 */
int main(void) {
    pthread_t tid, jid;
    uint8_t tmp;

    //Init semaphores for TX data handshake
    sem_unlink("/semaphore_tx_msp");
    sem_unlink("/semaphore_tx_cli");
    sem_tx_msp = sem_open("/semaphore_tx_msp", O_CREAT, 0644, 0);
    sem_tx_cli = sem_open("/semaphore_tx_cli", O_CREAT, 0644, 0);

    //Init queue for RX data
    init_queue();

    //Start thread for dynamixel module emulation
    pthread_create(&tid, NULL, dyn_emu, (void *) &tid);
    pthread_create(&jid, NULL, joystick_emu, (void *) &jid);

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

    printf("MAIN: Setting the left Motor(2) \n");
    endlessTurn(RIGHT_WHEEL);
    checkRegister(RIGHT_WHEEL, CCW_ANGLE_LIMIT_L, &tmp);
    assert(tmp == 0);
    checkRegister(RIGHT_WHEEL, CCW_ANGLE_LIMIT_H, &tmp);
    assert(tmp == 0);
    checkRegister(RIGHT_WHEEL, CW_ANGLE_LIMIT_L, &tmp);
    assert(tmp == 0);
    checkRegister(RIGHT_WHEEL, CW_ANGLE_LIMIT_H, &tmp);
    assert(tmp == 0);


    printf("\nMAIN: Setting the right Motor(3) \n");
    endlessTurn(LEFT_WHEEL);
    checkRegister(LEFT_WHEEL, CCW_ANGLE_LIMIT_L, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, CCW_ANGLE_LIMIT_H, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, CW_ANGLE_LIMIT_L, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, CW_ANGLE_LIMIT_H, &tmp);
    assert(tmp == 0);
    //wheelMode(0x02);

    printf("\nMAIN: FORWARD\n");
    forward(200);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 200);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 4);
    checkRegister(LEFT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 200);
    checkRegister(LEFT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 0);

    printf("\nMAIN: STOP\n");
    stop();
    checkRegister(RIGHT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 0);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 0);


    printf("\nMAIN: Turn left \n");
    turnLeft(150);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 150);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 0);

    stop();

    printf("\nMAIN: Turn right \n");
    turnRight(150);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 0);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 4);
    checkRegister(LEFT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 150);
    checkRegister(LEFT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 4);

    stop();

    printf("\nMAIN: Backward \n");
    backward(200);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 200);
    checkRegister(RIGHT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 0);
    checkRegister(LEFT_WHEEL, MOV_SPEED_L, &tmp);
    assert(tmp == 200);
    checkRegister(LEFT_WHEEL, MOV_SPEED_H, &tmp);
    assert(tmp == 4);

    printf("************************\n");
    printf("Test passed successfully\n");
    printf("Pulsar 'q' para terminar, qualquier tecla para seguir\r");
    fflush(stdout);//	return 0;

    while (estado != Quit) {
        Get_estado(&estado, &estado_anterior);
        if (estado != estado_anterior) {
            Set_estado_anterior(estado);
            printf("estado = %d\n", estado);
            fflush(stdout);
            switch (estado) {
                case Sw1:
                    printf("Boton Sw1 ('a') apretado\n");
                    break;
                case Sw2:
                    printf("Boton Sw2 ('s') apretado\n");
                    printf("MAIN:Moving to right and stop \n");
                    turnRight(1000);
                    stop();
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
