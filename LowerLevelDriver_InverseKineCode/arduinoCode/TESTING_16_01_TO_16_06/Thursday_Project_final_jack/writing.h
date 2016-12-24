/*********************************************************************
 * SD card read/write     
 **********************************************************************/

#ifndef WRITING_H
#define WRITING_H

#include <SPI.h>
#include <SD.h>
#include <stdlib.h>

#define JOINT_ARRAY_SIZE 300

typedef struct {
	char *movementName;
	uint16_t joint1[JOINT_ARRAY_SIZE];
	uint16_t joint2[JOINT_ARRAY_SIZE];
	uint16_t joint3[JOINT_ARRAY_SIZE];
	uint16_t joint4[JOINT_ARRAY_SIZE];
} movement;

extern File myFile;


/*********************************************************************
 * This function prints the data stored into  the struct
 * movement. The data is related to each angle that each joint
 * will be moved in each as a sequence. As a result, there are
 * arrays that stores these angles as a timeline.
 *********************************************************************/
void printDataRead (movement *m);


/*********************************************************************
 * Create the file of the txt format into FAT section into the SD card.
 * If the file exists, it is deleted and created again. 
 *********************************************************************/
void createFile();


/*********************************************************************
 * Write the array into the file in the SD card.
 * The data is written inside the file such:
 * 
 * m movementName1
 * joint1 angle1 angle2 [..] angleN
 * joint2 angle1 angle2 [..] angleN
 * joint3 angle1 angle2 [..] angleN
 * joint4 angle1 angle2 [..] angleN
 * m movementName2
 * [..]
 *********************************************************************/
void writeBuffer(movement *m);


/*********************************************************************
 * This function gets the name of the movement, which 
 * means that is the keyword that defines a movement.
 * The funcion get its name from a array of characters returned 
 * from the readLine function.
 *********************************************************************/
void getKeyword(char *line, int size, char *keyword);


/**********************************************************************
 * This function reads a whole line of the file
 * and returns an array of characters and its size.
 *********************************************************************/
void readLine(char *line, int *size);


/**********************************************************************
 * This function reads an empty line between two movements.
 *********************************************************************/
void readEmptyLine();


/**********************************************************************
 * This function reads an angle from the file and returns the value
 * in the parameter angle.
 *********************************************************************/
void readAngle(uint32_t *angle, char c);


/**********************************************************************
 * This function reads an line of angles. The parameter storeFlag is
 * used to decide to store the angles read or not. The case that the line
 * of angles is not from the movement that the user searched the values
 * should not be stored. This could be done using seek function.
 *********************************************************************/
void readAngleLine(uint8_t storeFlag, movement *m, uint8_t jointIndex);


/*********************************************************************
 * This function adds the angle read from the movements file into the properly
 * joint array into the movement struct.
 * The parameter 'jointIndex' indicate the joint array.
 * The parameter 'index' indicate the index of the array.
 * The parameter 'value' is the angle.
 *********************************************************************/
void addJointData(movement *m, uint8_t jointIndex, int index, uint16_t value);


/*********************************************************************
 * This function reads a joint line and stores each angles into the 
 * properly joint array into the struct using the addJointData function.
 * The parameter 'jointIndex' indicate the joint array(joint1 or joint2, so on).
 *********************************************************************/
void getJointData(char *line, int size, movement *m, uint8_t jointIndex);


/*********************************************************************
 * Reads the movement from the movements file into the SD card
 * and stores it into the struct.
 *********************************************************************/
void readMoviment(movement *m1, char * movementName, int size);


/*********************************************************************
 * This function checks if two character array is equal,
 * returning 1 if is equal or 0 otherwise.
 *********************************************************************/
uint8_t isEqual(char *s1 , char *s2);


/**********************************************************************
 * This function writes the name of each movement, entered by the user,
 * to a different file. This names will be used in the searchMachine
 * function.
 *********************************************************************/
void writeCommandName(char *command);


/**********************************************************************
 * This function read a name from the file of movement names to be
 * used in the searchMachine.
 *********************************************************************/
void readName(char *commandName, File namesFile);


/**********************************************************************
 * This function read all names from the file of movement names to be
 * used in the searchMachine.
 *********************************************************************/
void readCommandNames();


/*********************************************************************
 * This function get the data from the movements file, which movement name
 * is equal to the parameter 'movementName'. 
 * Returns 1 if the movement was found or 0 otherwise.
 *********************************************************************/
uint8_t getMovement(movement *m1, char *movementName);


/*********************************************************************
 * This function write multiple movements into the file in the SD
 * card.
 *********************************************************************/
void saveMovements(movement *movementArray, int lenght);


/*********************************************************************
 * This function populate the struct with data for the sake of
 * testing.
 *********************************************************************/
void generateMovementData(movement* m, int size);

#endif
