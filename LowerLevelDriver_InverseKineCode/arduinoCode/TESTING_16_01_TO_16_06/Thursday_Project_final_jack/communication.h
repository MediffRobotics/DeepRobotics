#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdio.h>
#include "writing.h"


/*****************************************************************
 * WRITE_TO_SERIAL3 FUNCTION 
 * The function writes 4 bytes to the Serial3 port. 
 ****************************************************************/
void write_to_serial3(uint32_t num);


/*****************************************************************
 * READ_FROM_SERIAL3 FUNCTION
 * The function reads 4 bytes from Serial3 port and return it. If
 * the number of bytes read, which is returned from the function
 * readBytes, does not correspond to 4 bytes the funtion returns -1.
 ****************************************************************/
uint32_t read_from_serial3();


/*****************************************************************
 * SAVEMOVEMENTDATA FUNCTION
 * This function send the data in the struct movement to the other
 * arduino throuh the Serial3 port. The value 200 at the end of 
 * each joint array indicate the end of the array.
 ****************************************************************/
void sendMovementData(movement *m);


/*****************************************************************
 * RECEIVEMOVEMENTDATA FUNCTION
 * This function receives the movement data from the other arduino.
 * The value 200 at the end of each joint array indicate the end
 * of the array.
 ****************************************************************/
void receiveMovementData(movement *m);

#endif
