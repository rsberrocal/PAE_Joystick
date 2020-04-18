//
// Created by Rocho on 18/04/2020.
//

#include "dyn_motors.h"
#include "dyn_frames.h"

void wheelMode(void){
    //Creating instruction
    byte id = 0xFE;//BROADCASTING
    byte instruccion = 0x03; //WRITE_DATA
    byte paramsLength = 5; //Number of data to write +1
    byte parameters[16];

    parameters[0] = 0x06;//Start at CW_ANGLE_LIMIT_L

    parameters[1] = 0; // CW_ANGLE_LIMIT_L = 0
    parameters[2] = 0; // CW_ANGLE_LIMIT_H = 0
    parameters[3] = 0; // CCW_ANGLE_LIMIT_L = 0
    parameters[4] = 0; // CCW_ANGLE_LIMIT_H = 0

    TxPacket(id,paramsLength,instruccion,parameters);
}

void moveWheel(byte ID, bool rotation,unsigned int speed){

    

}