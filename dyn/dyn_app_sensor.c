/*
 * dyn_sensor.c
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 *
 * TODO: High-level functions like "distance_wall_front", etc
 * TODO: Generate another file for motors, with functions like "move_forward", etc
 */
#include "dyn_app_sensor.h"
#include "dyn_instr.h"

int redObsDetDistance(int ID, byte postion){
    int distance;
    byte param[16];
    param[0] = 1;

    distance = dyn_read_byte(ID, postion,param);

    return distance;
}


int sensorRead(byte ID, byte sensor){
    int distance;
    byte param[16];
    param[0] = 1;

    distance = dyn_read_byte(ID, sensor, param);

    return distance;
}


int getObstacleFlag(byte ID){
    byte flags;
    byte param[16];
    param[0] = 1;

    flags = dyn_read_byte(ID, 0x20,param);

    return flags;
}




