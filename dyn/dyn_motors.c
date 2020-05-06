//
// Created by Rocho on 18/04/2020.
//

#include "dyn_motors.h"
#include "dyn_frames.h"
#include "dyn_instr.h"

void endlessTurn(byte idMotor) {
    //ID will not be broadcasting because the emulator, so setting the two motors manually
    //start writing at CW_ANGLE_LIMIT_L
    //params will be
    byte params[4] = {0, 0, 0, 0};
    // CW_ANGLE_LIMIT_L = 0
    // CW_ANGLE_LIMIT_H = 0
    // CCW_ANGLE_LIMIT_L = 0
    // CCW_ANGLE_LIMIT_H = 0
    dyn_write(idMotor, 0x06, params, 4);
}

//moveTo true -> right; false -> left
void moveWheel(byte ID, bool moveTo, unsigned int speed) {
    byte speed_H, speed_L;
    speed_L = speed; //speed always will be les than 1024

    //To rotate
    if (moveTo) { //rotate to right means CW 4, MOVING SPEED H 0100
        speed_H = (speed >> 8) + 4;
    } else { //rotate to right means CCW 0, MOVING SPEED H 0000
        speed_H = speed >> 8;
    }

    //Start at mov speed low
    byte params[2] = {speed_L, speed_H};
    //params will be
    // MOV_SPEED_L = speed_L
    // MOV_SPEED_H = speed_H
    dyn_write(ID, MOV_SPEED_L, params, 2);
}

void stop(void) {
    //With
    moveWheel(RIGHT_WHEEL, false, 0);
    moveWheel(LEFT_WHEEL, false, 0);
}

void turnLeft(unsigned int speed) {
    if (speed < MAX_SPEED) {
        moveWheel(RIGHT_WHEEL, true, speed);
        moveWheel(LEFT_WHEEL, true, 0);
    }
}

void turnOnItselfLeft(unsigned int speed) {
    if (speed < MAX_SPEED) {
        moveWheel(RIGHT_WHEEL, true, speed);
        moveWheel(LEFT_WHEEL, true, speed);
    }
}

void turnRight(unsigned int speed) {
    if (speed < MAX_SPEED) {
        moveWheel(RIGHT_WHEEL, false, 0);
        moveWheel(LEFT_WHEEL, false, speed);
    }
}


void turnOnItselfRight(unsigned int speed) {
    if (speed < MAX_SPEED) {
        moveWheel(RIGHT_WHEEL, false, speed);
        moveWheel(LEFT_WHEEL, false, speed);
    }
}

void forward(unsigned int speed) {
    if (speed < MAX_SPEED) {
        moveWheel(RIGHT_WHEEL, true, speed);
        moveWheel(LEFT_WHEEL, false, speed);
    }
}

void backward(unsigned int speed) {
    if (speed < MAX_SPEED) {
        moveWheel(RIGHT_WHEEL, false, speed);
        moveWheel(LEFT_WHEEL, true, speed);
    }
}