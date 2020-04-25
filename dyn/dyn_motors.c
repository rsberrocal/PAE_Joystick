//
// Created by Rocho on 18/04/2020.
//

#include "dyn_motors.h"
#include "dyn_frames.h"

void wheelMode(byte idMotor) {
    //Creating instruction
    byte id = idMotor;//Not broadcasting for the emulator so setting the two motors manually
    byte instruccion = 0x03; //WRITE_DATA
    byte paramsLength = 5; //Number of data to write +1
    byte parameters[16];

    parameters[0] = 0x06;//Start at CW_ANGLE_LIMIT_L

    parameters[1] = 0; // CW_ANGLE_LIMIT_L = 0
    parameters[2] = 0; // CW_ANGLE_LIMIT_H = 0
    parameters[3] = 0; // CCW_ANGLE_LIMIT_L = 0
    parameters[4] = 0; // CCW_ANGLE_LIMIT_H = 0

    TxPacket(id, paramsLength, instruccion, parameters);
}

//moveTo true -> right; false -> left
void moveWheel(byte ID, bool moveTo, unsigned int speed) {

    struct RxReturn returnPacket;
    byte speed_H, speed_L;
    speed_L = speed; //speed always will be les than 1024

    //To rotate
    if (moveTo) { //rotate to right means CW 4, MOVING SPEED H 0100
        speed_H = (speed >> 8) + 4;
    } else { //rotate to right means CCW 0, MOVING SPEED H 0000
        speed_H = speed >> 8;
    }

    byte instr = WRITE_DATA;//Write data
    byte paramsLength = 3;
    byte parameters[16];

    parameters[0] = MOV_SPEED_L; //Start at mov speed low

    parameters[1] = speed_L; //write low
    parameters[2] = speed_H; //write high

    TxPacket(ID, paramsLength, instr, parameters);
    returnPacket = RxPacket();
}

void stop(void) {
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

void endlessTurn(unsigned int speed) {

}