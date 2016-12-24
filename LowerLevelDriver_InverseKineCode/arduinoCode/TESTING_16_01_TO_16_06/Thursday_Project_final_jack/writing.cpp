/*********************************************************************
 * SD card read/write     
 **********************************************************************/
 
#include "writing.h"

/*********************************************************************
 * This function prints the data stored into  the struct
 * movement. The data is related to each angle that each joint
 * will be moved in each as a sequence. As a result, there are
 * arrays that stores these angles as a timeline.
 *********************************************************************/
void printDataRead (movement *m)
{
	int i = 0;
	Serial.println("\nMovement: ");
	Serial.println(m->movementName);
	
	Serial.print("Joint1 ");
	while( i < JOINT_ARRAY_SIZE && m->joint1[i] <= 180){
			Serial.print(m->joint1[i]);
			Serial.print(" ");
			i++;
	}
	
	i = 0;
	Serial.println("");
	Serial.print("Joint2 ");
	while( i < JOINT_ARRAY_SIZE && m->joint2[i] <= 180){
			Serial.print(m->joint2[i]);
			Serial.print(" ");
			i++;
	}
	
	i = 0;
	Serial.println("");
	Serial.print("Joint3 ");
	while(i < JOINT_ARRAY_SIZE && m->joint3[i] <= 180){
			Serial.print(m->joint3[i]);
			Serial.print(" ");
			i++;
	}

	i = 0;
	Serial.println("");
	Serial.print("Joint4 ");
	while(i < JOINT_ARRAY_SIZE && m->joint4[i] <= 180){
			Serial.print(m->joint4[i]);
			Serial.print(" ");
			i++;
	}
}


/*********************************************************************
 * Create the file of the txt format into FAT section into the SD card.
 * If the file exists, it is deleted and created again. 
 *********************************************************************/
void createFile()
{

	// Check to see if the file exists:
	if (SD.exists("anglesr.txt")) {
		Serial.println("The file anglesr.txt already exists.");
		
		// delete the file:		
		if (SD.remove("anglesr.txt")){
			Serial.println("Removing existing anglesr.txt");
		} else {
			Serial.println("The file anglesr.txt could not be removed.");
		}
	} else {
		Serial.println("The file anglesr.txt doesn't exist.");  
	}

	//raw blocks
	myFile = SD.open("anglesr.txt", FILE_WRITE);
	
	if (myFile) {
		Serial.println("Creating a file called anglesr.txt.");		
		myFile.close();
		
	} else {
		Serial.println("Error: File anglesr.txt could not be created.");
	}
	
	//Deleting the names.txt file
	if (SD.exists("names.txt")) {
		Serial.println("The file names.txt already exists.");
		
		// delete the file:		
		if (SD.remove("names.txt")){
			Serial.println("Removing existing names.txt");
		} else {
			Serial.println("The file names.txt could not be removed.");
		}
	}
}


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
void writeBuffer(movement *m)
{	
	myFile = SD.open("anglesr.txt", FILE_WRITE);
	int i = 0;
	Serial.println("");
	
	
	if (myFile) {
		myFile.print("m ");
		myFile.print(m->movementName);
		myFile.print("joint1 ");
		
		while (i < JOINT_ARRAY_SIZE && m->joint1[i] <= 180){
			myFile.print(m->joint1[i]);
			myFile.print(" ");	
			i++;		
		}
		Serial.print("Number of angles saved for Joint1: ");
		Serial.println(i);
		myFile.print("\n");
		myFile.print("joint2 ");
		i = 0;		
		while(i < JOINT_ARRAY_SIZE && m->joint2[i] <= 180){
			myFile.print(m->joint2[i]);
			myFile.print(" ");
			i++;		
		}
		Serial.print("Number of angles saved for Joint2: ");
		Serial.println(i);		
		myFile.print("\n");
		myFile.print("joint3 ");
		
		i = 0;		
		while(i < JOINT_ARRAY_SIZE && m->joint3[i] <= 180){
			myFile.print(m->joint3[i]);
			myFile.print(" ");
			i++;		
		}
		Serial.print("Number of angles saved for Joint3: ");
		Serial.println(i);		
		myFile.print("\n");
		myFile.print("joint4 ");
		
		i = 0;		
		while(i < JOINT_ARRAY_SIZE && m->joint4[i] <= 180){
			myFile.print(m->joint4[i]);
			myFile.print(" ");
			i++;	
		}
		Serial.print("Number of angles saved for Joint4: ");
		Serial.println(i);
		myFile.print("\n\n");
		myFile.close();
		
		writeCommandName(m->movementName);
		
		//Testing
			readCommandNames();
		//end testing
		
	} else {
		Serial.println("\nError: The file anglesr.txt could not be opened.");
	}
}

/*********************************************************************
 * This function gets the name of the movement, which 
 * means that is the keyword that defines a movement.
 * The funcion get its name from a array of characters returned 
 * from the readLine function.
 *********************************************************************/
void getKeyword(char *line, int size, char *keyword)
{	
	int j = 0;

	for (int i = 2; i < size; i++){
		keyword[j] = line[i];
		j++;
	}
	keyword[j] = '\0';
}

/**********************************************************************
 * This function reads a whole line of the file
 * and returns an array of characters and its size.
 *********************************************************************/
void readLine(char *line, int *size)
{
	char c = myFile.read();

	int index = 0;
	
	while(c != '\n' && c != 13){
		line[index] = c;
		index++;
		c = myFile.read();
	}
	
	line[index] = '\0';
	*size = index;
}

/**********************************************************************
 * This function reads an empty line between two movements.
 *********************************************************************/
void readEmptyLine(){
	char c = 'b';
	
	while (c != '\n'){
		c = myFile.read();
	}	
}

/**********************************************************************
 * This function reads an angle from the file and returns the value
 * in the parameter angle.
 *********************************************************************/
void readAngle(uint32_t *angle, char c){
	char number[15];
	int index = 0;
	
	//Reading an angle
	while(c != ' ' && c != '\n' && c != 13){			
		number[index] = c;
		index++;
		c = myFile.read();
	}
	number[index] = '\0';
	*angle = atoi(number);
}

/**********************************************************************
 * This function reads an line of angles. The parameter storeFlag is
 * used to decide to store the angles read or not. The case that the line
 * of angles is not from the movement that the user searched the values
 * should not be stored. This could be done using seek function.
 *********************************************************************/
void readAngleLine(uint8_t storeFlag, movement *m, uint8_t jointIndex){
	char c;
	int index = 0;
	int i = 0;
	int arrayIndex = 0;
	uint32_t num = 0;
	c = myFile.read();
	
	//Reading joint name
	while(c != ' ' && c != '\0'){			
		c = myFile.read();
	}
	
	//Reading first number
	c = myFile.read();
	
	//Reading joint data
	while (c != '\n' && c != '\0' && c != ' ' && c != '\r'){
		
		readAngle(&num, c);
		if(storeFlag){		
			addJointData(m, jointIndex, arrayIndex, num);
			arrayIndex++;
		}
		
		c = myFile.read();
	}
	Serial.println("");
	if(storeFlag){
		addJointData(m, jointIndex, arrayIndex, 200);
	}
}


/*********************************************************************
 * This function adds the angle read from the movements file into the properly
 * joint array into the movement struct.
 * The parameter 'jointIndex' indicate the joint array.
 * The parameter 'index' indicate the index of the array.
 * The parameter 'value' is the angle.
 *********************************************************************/
void addJointData(movement *m, uint8_t jointIndex, int index, uint16_t value)
{
	if (jointIndex == 1){
		m->joint1[index] = value;
		
	} else if (jointIndex == 2){
		m->joint2[index] = value;
	
	} else if (jointIndex == 3){
		m->joint3[index] = value;
	
	} else if (jointIndex == 4){
		m->joint4[index] = value;
	}	
}

/*********************************************************************
 * This function reads a joint line and stores each angles into the 
 * properly joint array into the struct using the addJointData function.
 * The parameter 'jointIndex' indicate the joint array(joint1 or joint2, so on).
 *********************************************************************/
void getJointData(char *line, int size, movement *m, uint8_t jointIndex)
{
	char c;
	int index = 0;
	int i = 0;
	uint32_t num = 0;
	c = 'b';
	
	//Reading joint name
	while(c != ' ' && c != '\0'){			
		c = line[i];
		i++;
	}
	
	char number[15];
	int arrayIndex = 0;
	c = line[i];
	i++;
	
	//Reading joint data
	while (c != '\n' && c != '\0' && c != ' ' && c != '\r' && i < size){
		index = 0;
		
		//Reading an angle
		while(c != ' '){			
			number[index] = c;
			index++;
			c = line[i];
			i++;
		}
		number[index] = '\0';
		num = atoi(number);
		addJointData(m, jointIndex, arrayIndex, num);
		arrayIndex++;
		c = line[i];
		i++;
	}
	addJointData(m, jointIndex, arrayIndex, 200);
}

/*********************************************************************
 * Reads the movement from the movements file into the SD card
 * and stores it into the struct.
 *********************************************************************/
void readMoviment(movement *m1, char * movementName, int size)
{
	char line[700];
	char name[15];
	m1->movementName = movementName;
	readAngleLine(1, m1, 1);			//joint1
	readAngleLine(1, m1, 2);			//joint2
	readAngleLine(1, m1, 3);			//joint3			
	readAngleLine(1, m1, 4);			//joint4
}


/*********************************************************************
 * This function checks if two character array is equal,
 * returning 1 if is equal or 0 otherwise.
 *********************************************************************/
uint8_t isEqual(char *s1 , char *s2)
{
	int i = 0;
	uint8_t result = 1;
	
	while (s1[i] != '\0' && s1[i] != NULL && s2[i] != '\0' && s2[i] != NULL){		
		if (s1[i] != s2[i]){
			result = 0;
			 break;
		 }
		 i++;
	}
	return result;
}

/**********************************************************************
 * This function writes the name of each movement, entered by the user,
 * to a different file. This names will be used in the searchMachine
 * function.
 *********************************************************************/
void writeCommandName(char *command){

		File namesFile = SD.open("names.txt", FILE_WRITE);
	
		if (namesFile) {
			namesFile.print(command);
			namesFile.print("\n");					
			namesFile.close();
		} else {
			Serial.println("Error: File names.txt could not be created.");
		}	  
}

/**********************************************************************
 * This function read a name from the file of movement names to be
 * used in the searchMachine.
 *********************************************************************/
void readName(char *commandName, File namesFile){
	char c;
	int i = 0;
	c = namesFile.read();

	//Reading the name until find a end of line
	while(c != '\n' && c != 13){
		commandName[i] = c;
		i++;
		c = namesFile.read();
	}

	//end of the string
	commandName[i] = '\0';	
}

/**********************************************************************
 * This function read all names from the file of movement names to be
 * used in the searchMachine.
 *********************************************************************/
void readCommandNames(){
		
	File namesFile = SD.open("names.txt", FILE_READ);
	char name1[100];
	
	if (namesFile) {
		Serial.println("List of names from the file: ");
		
		//Reading all the names from the file
		while(namesFile.available()){
			readName(name1, namesFile);
			Serial.println(name1);
		}			
		namesFile.close();
		Serial.println("");
	} else {
		Serial.println("Error: File names.txt could not be created.");
	}
}

/*********************************************************************
 * This function get the data from the movements file, which movement name
 * is equal to the parameter 'movementName'. 
 * Returns 1 if the movement was found or 0 otherwise.
 *********************************************************************/
uint8_t getMovement(movement *m1, char *movementName)
{	
	myFile = SD.open("anglesr.txt", FILE_READ);
	char c;
	char line[700];
	char *name;
	int size = 0;
	int i = 0, j = 0;
	uint8_t itemFound = 0;
	
	if (myFile) {
		
		 // Read from the file until there's nothing else to read
		  while (myFile.available()) {
				readLine(line, &size);					//Command name: keyword
				name = (char *) malloc(sizeof(char)*(size));
				getKeyword(line, size, name);
				
				Serial.print("From the file: ");
				Serial.println(name);
				
				//If the movement is what it was searched
				if (isEqual(name, movementName)){
					Serial.println("Found");
					readMoviment(m1, movementName, size);
					itemFound = 1;
					break;
				
				//Reading the file without storing any value	
				} else {
					Serial.println("Not Found");				
					readAngleLine(0, NULL, 0);			//joint1		
					readAngleLine(0, NULL, 0);			//joint2			
					readAngleLine(0, NULL, 0);			//joint3					
					readAngleLine(0, NULL, 0);			//joint4			
					readEmptyLine();					//empty line
				}
		  }
		    myFile.close();
			
	} else {
		Serial.println("\nerror opening .txt");
	}

	return itemFound;
}


/*********************************************************************
 * This function write multiple movements into the file in the SD
 * card.
 *********************************************************************/
void saveMovements(movement *movementArray, int lenght){
	for (int i = 0; i < lenght; i++){
			writeBuffer(&movementArray[i]);
	}
}

/*********************************************************************
 * This function populate the struct with data for the sake of
 * testing.
 *********************************************************************/
void generateMovementData(movement* m, int size)
{
	char *names[] = {"Apple", "Orange", "bread"};
	int num = 10;
	int j = 0;
	
	for (int i = 0; i < size; i++){
		//m[i].movementName = names[i];
		
		for(j = 0; j < 50; j++){
			m[i].joint1[j] = num;
		}
		m[i].joint1[j] = 200;
		num = num + 5;
		
		for(j = 0; j < 50; j++){
			m[i].joint2[j] = num;
		}
		m[i].joint2[j] = 200;
		num = num + 5;
		
		for(j = 0; j < 50; j++){
			m[i].joint3[j] = num;
		}
		m[i].joint3[j] = 200;
		num = num + 5;
		
		for(j = 0; j < 50; j++){
			m[i].joint4[j] = num;
		}
		m[i].joint4[j] = 200;
	}	
}

