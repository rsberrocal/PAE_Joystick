/*
 * hal_dyn_uart.c
 *
 *  Created on: 22 mar. 2020
 *      Author: droma
 */

#include "../hal_dyn_uart/hal_dyn_uart.h"

#include "msp.h"
#define TXD2_READY (UCA2IFG & UCTXIFG)

/* funcions per canviar el sentit de les comunicacions */
void Sentit_Dades_Rx(void) { //Configuraci� del Half Duplex dels motors: Recepci�
	P3OUT &= ~BIT0;   //El pin P3.0 (DIRECTION_PORT) el posem a 0 (Rx)
}

void Sentit_Dades_Tx(void) { //Configuraci� del Half Duplex dels motors: Transmissi�
	P3OUT |= BIT0;    //El pin P3.0 (DIRECTION_PORT) el posem a 1 (Tx)
}

/* funci� TxUAC0(byte): envia un byte de dades per la UART 0 */
void TxUAC2(byte bTxdData) {
	while (!TXD2_READY)
		;   // Espera a que estigui preparat el buffer de transmissi�
	UCA2TXBUF = bTxdData;
}

void EUSCIA2_IRQHandler(void) {  //interrupcion de recepcion en la UART A2
//UCA2IE &= ~UCRXIE; //Interrupciones desactivadas en RX
	DatoLeido_UART = UCA2RXBUF;
	Byte_Recibido = true;
	//UCA2IE |= UCRXIE; //Interrupciones reactivadas en RX
}

void Activa_Timer_TimeOut() {
	// TODO: Implementar iniciar timer
}


void Reset_Timeout() {
	// TODO: Implementar reset comptador time out
}

bool TimeOut(uint16_t cnt) {
	// TODO: Implementar check time out
	return false;
}

void rx_uart_byte(struct RxReturn respuesta) {
	Byte_Recibido = false;  //No_se_ha_recibido_Byte();
	Reset_Timeout();
	while (!Byte_Recibido) //Se_ha_recibido_Byte())
	{
		respuesta.time_out = TimeOut(1000); // tiempo en decenas de microsegundos (ara 10ms)
		if (respuesta.time_out)
			break;  //sale del while
	}
	if (!respuesta.time_out) {
		respuesta.StatusPacket[respuesta.idx++] = DatoLeido_UART;
	}

}
