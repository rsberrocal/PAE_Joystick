/*
 * b_queue.h
 *
 *  Created on: 22 mar. 2020
 *      Author: droma
 */

#ifndef DYN_TEST_B_QUEUE_H_
#define DYN_TEST_B_QUEUE_H_

#include <stdint.h>
#include <pthread.h>

typedef struct Queue_t {
	uint8_t data[32];
	uint8_t idx_pop;
	uint8_t idx_push;
	uint8_t data_pending;
	pthread_mutex_t mutex;
} Queue;

typedef enum _queue_ret
{
    QUEUE_OK = 0,
	QUEUE_EMPTY = 1,
    QUEUE_FULL = 2,
	QUEUE_ERR = 3,
} QUEUE_RET;

void init_queue();
QUEUE_RET queue_push(uint8_t data);
QUEUE_RET queue_pop(uint8_t* data);

#endif /* DYN_TEST_B_QUEUE_H_ */
