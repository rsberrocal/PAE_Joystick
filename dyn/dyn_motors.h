//
// Created by Rocho on 18/04/2020.
//

#ifndef JOYSTICK_DYN_MOTORS_H
#define JOYSTICK_DYN_MOTORS_H
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t byte;

void wheelMode(void);//to rotate wheels

void moveWheel(byte ID, bool rotation,unsigned int speed);

void stop(void);

void turnLeft(unsigned int speed);

void turnLeftD(unsigned int degree);

void turnOnItselfLeft(unsigned int speed);

void turnRight(unsigned int speed);

void turnRightD(unsigned int degree);

void turnOnItselfRight(unsigned int speed);

void forward(unsigned int speed);

void backward(unsigned int speed);




#endif //JOYSTICK_DYN_MOTORS_H
