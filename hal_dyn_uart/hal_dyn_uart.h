/*
 * hal_dyn_uart.h
 *
 *  Created on: 22 mar. 2020
 *      Author: droma
 */

#ifndef HAL_DYN_UART_H_
#define HAL_DYN_UART_H_

#include <stdbool.h>
#include <stdint.h>
#include "dyn/dyn_frames.h"

volatile uint8_t DatoLeido_UART;
volatile bool Byte_Recibido;

void Sentit_Dades_Rx(void);
void Sentit_Dades_Tx(void);

void TxUAC2(byte bTxdData);

void Activa_Timer_TimeOut();
void Reset_Timeout();
bool TimeOut(uint16_t cnt);

void rx_uart_byte(struct RxReturn respuesta);

#endif /* HAL_DYN_UART_H_ */
