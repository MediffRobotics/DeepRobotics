#include "communication.h"


/*****************************************************************
 * WRITE_TO_SERIAL3 FUNCTION 
 * The function writes 4 bytes to the Serial3 port. 
 ****************************************************************/
void write_to_serial3(uint32_t num)
{
    //Returns the number of bits written
    int bytes_written = Serial3.write((uint8_t*)&num, 4);
    
    if (bytes_written != 4){
		Serial.println("The 4 bytes weren't written.");
    }
}


/*****************************************************************
 * READ_FROM_SERIAL3 FUNCTION
 * The function reads 4 bytes from Serial3 port and return it. If
 * the number of bytes read, which is returned from the function
 * readBytes, does not correspond to 4 bytes the funtion returns -1.
 ****************************************************************/
uint32_t read_from_serial3()
{
    uint32_t num = 0;
    int bytes_read = Serial3.readBytes((char *)&num, 4);
    
    if (bytes_read != 4){
		Serial.println("The 4 bytes weren't read.");
		return -1;
    }
  
    return num;
}


/*****************************************************************
 * SAVEMOVEMENTDATA FUNCTION
 * This function send the data in the struct movement to the other
 * arduino throuh the Serial3 port. The value 200 at the end of 
 * each joint array indicate the end of the array.
 ****************************************************************/
void sendMovementData(movement *m)
{
	uint32_t num = 0;
	int i = 0;
	Serial.println("");
	
	//Sending the angles of the joint1
	while( i < JOINT_ARRAY_SIZE && m->joint1[i] <= 180){
			num = m->joint1[i];
			write_to_serial3(num);
			i++;
			delay(50);
			
	}
	//Sending a value to indicate the end of the joint1 data
	num = 200;
	Serial.print("Number of angles sent for Joint1: ");
	Serial.println(i);
	Serial3.write((uint8_t*)&num, 4);
	
	//Sending the angles of the joint2
	i = 0;
	while( i < JOINT_ARRAY_SIZE && m->joint2[i] <= 180){
			num = m->joint2[i];
			write_to_serial3(num);
			i++;
			delay(50);
	}
	//Sending a value to indicate the end of the joint2 data
	num = 200;
	Serial.print("Number of angles sent for Joint2: ");
	Serial.println(i);
	Serial3.write((uint8_t*)&num, 4);	
	
	//Sending the angles of the joint3
	i = 0;
	while(i < JOINT_ARRAY_SIZE && m->joint3[i] <= 180){
			num = m->joint3[i];
			write_to_serial3(num);
			i++;
			delay(50);
	}
	//Sending a value to indicate the end of the joint3 data
	num = 200;
	Serial.print("Number of angles sent for Joint3: ");
	Serial.println(i);
	Serial3.write((uint8_t*)&num, 4);
	
	//Sending the angles of the joint4
	i = 0;
	while(i < JOINT_ARRAY_SIZE && m->joint4[i] <= 180){
			num = m->joint4[i];
			write_to_serial3(num);
			i++;
			delay(50);
	}
	Serial.print("Number of angles sent for Joint4: ");
	Serial.println(i);
	
	//Sending a value to indicate the end of the joint4 data
	num = 200;
	write_to_serial3(num);
	delay(50);
}


/*****************************************************************
 * RECEIVEMOVEMENTDATA FUNCTION
 * This function receives the movement data from the other arduino.
 * The value 200 at the end of each joint array indicate the end
 * of the array.
 ****************************************************************/
void receiveMovementData(movement *m)
{
	uint32_t num = 0;
	int i = 0;
	Serial.println("");
	
	while( Serial3.available() < 0){}
	
	//Reads all the data from joint 1
	while(true){
		if ( Serial3.available() > 0){
			num = read_from_serial3();			
			if (num >= 200) break;
			m->joint1[i] = num;
			i++;
		}
	}
	Serial.print("Number of angles received for Joint1: ");
	Serial.println(i);
	
	//Set the end of the data for the joint1
	m->joint1[i] = 200;
	
	//Reads all the data from joint 2
	i = 0;
	while( true){
		if (Serial3.available() > 0){
			num = read_from_serial3();			
			if (num >= 200) break;
			m->joint2[i] = num;
			i++;
		}
	}
	Serial.print("Number of angles received for Joint2: ");
	Serial.println(i);
	
	//Set the end of the data for the joint2
	m->joint2[i] = 200;	
	
	//Reads all the data from joint 3
	i = 0;
	while(true){
		if ( Serial3.available() > 0){
			num = read_from_serial3();				
			if (num >= 200) break;
			m->joint3[i] = num;
			i++;
		}
	}
	Serial.print("Number of angles received for Joint3: ");
	Serial.println(i);
	
	//Set the end of the data for the joint3
	m->joint3[i] = 200;
	
	//Reads all the data from joint 4
	i = 0;
	while( true){
		if ( Serial3.available() > 0){
			num = read_from_serial3();				
			if (num >= 200) break;
			m->joint4[i] = num;
			i++;
		}
	}
	Serial.print("Number of angles received for Joint4: ");
	Serial.println(i);
	
	//Set the end of the data for the joint4
	m->joint4[i] = 200;
}
