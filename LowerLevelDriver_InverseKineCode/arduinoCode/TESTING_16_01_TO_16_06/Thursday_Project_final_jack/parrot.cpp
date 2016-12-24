#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#include "lcd_image.h"
#include <Servo.h>
#include "communication.h"

/************************Declaration for recording movements***********/
movement movement1; 
int NumJoinArrayLength=0;
char signal = ' ';

/*****************************For controlling Servos*******************/

typedef struct {
#define NUM_SERVOS 4
	//For servos 	
	int numServos;
	int servoPins[NUM_SERVOS];
	int servoAngles[NUM_SERVOS];// Stands for servo a-d
	Servo myservo[NUM_SERVOS];
	int pos;
    int MaxChars; 	// an int string contains up to 5 digits and is terminated 
					//by a 0 to indicate end of string
					
	char strValue[NUM_SERVOS]; // must be big enough for digits and terminating null
	int index ; // the index into the array storing the received digits
	
			
}ServoGlobal;
ServoGlobal MyServoGlobal;

/**
 * Initialize Servos
 * */
void InitServos(){
	
	//Initialize the global variables
	
	MyServoGlobal.numServos=NUM_SERVOS;	
	MyServoGlobal.servoPins[0] = 8;// servos on pins 8 through 11
	MyServoGlobal.servoPins[1] = 9;// servos on pins 8 through 11
	MyServoGlobal.servoPins[2] = 10;// servos on pins 8 through 11
	MyServoGlobal.servoPins[3] = 11;// servos on pins 8 through 11
	MyServoGlobal.myservo;
	MyServoGlobal.pos =0;
	MyServoGlobal.MaxChars = 2; // an int string contains up to 5 
								//digits and is terminated by a 0 to
								// indicate end of string
	MyServoGlobal.strValue; 	// must be big enough for digits and terminating null
	MyServoGlobal.index = 0; // the index into the array storing the received digits
	
	//Initialize the hardwares	
	
	for(int i=0; i < MyServoGlobal.numServos; i++){
	MyServoGlobal.myservo[i].attach(MyServoGlobal.servoPins[i]);}

    //Initiate servos' positing 
		
    MyServoGlobal.servoAngles['a' - 'a']=50;
    MyServoGlobal.servoAngles['b' - 'a']=70;
    MyServoGlobal.servoAngles['c' - 'a']=180;
    MyServoGlobal.servoAngles['d' - 'a']=130;

    MyServoGlobal.myservo['a' - 'a'].write(MyServoGlobal.servoAngles['a' - 'a']);
    MyServoGlobal.myservo['b' - 'a'].write(MyServoGlobal.servoAngles['b' - 'a']);
    MyServoGlobal.myservo['c' - 'a'].write(MyServoGlobal.servoAngles['c' - 'a']);
    MyServoGlobal.myservo['d' - 'a'].write(MyServoGlobal.servoAngles['d' - 'a']);
}

/**
 * Controlling Servos using serial port
 * */

void SerialControllingServos(){
	if( Serial.available())
		{          
			char ch = Serial.read();
			if(MyServoGlobal.index <= 
					MyServoGlobal.MaxChars && ch >= '0' && ch <= '9'){
						
				// add the ASCII character to the string;
				MyServoGlobal.strValue[MyServoGlobal.index++] = ch;       
				
			}	// is 'a' letter for our servos?
			else if(ch >= 'a' && ch <= 'a'+ MyServoGlobal.numServos) 
			 { 			
				 
				  Serial.println(MyServoGlobal.strValue);     
				                 
				  // use atoi to convert the string to an int 
				  MyServoGlobal.pos = atoi(MyServoGlobal.strValue);   
				          							
				  MyServoGlobal.myservo[ch - 'a'].write(MyServoGlobal.pos);	
				  MyServoGlobal.index=0;		 
				  Serial.print(MyServoGlobal.strValue);
				  Serial.println(ch);	
				  
			}
		}
}

/************************* Using Joysticks*****************************/

/**
 * Global declaration
 * */
typedef struct {
	

	//The critical direction values of joysticks
	int JOY_LeftBig;
	int JOY_RightLess;
	int JOY_UpBig;
	int JOY_DownLess;
	
	//Joystick Hardware
	int JOYSTICK_SEL; 
    int JOYSTICK_VER;
    int JOYSTICK_HOR;	

}JoystickGlobal;
JoystickGlobal MyLeftJoystick;
JoystickGlobal MyRightJoystick;

/**
 * Initialize the two joysticks
 * */
void InitJoysticks(){
	
	//////Initialize Left Joystick		
	MyLeftJoystick.JOYSTICK_VER=0; //pin number
	MyLeftJoystick.JOYSTICK_HOR=1;
	

	/////Initialize Right Joystick
	MyRightJoystick.JOYSTICK_VER=2; //pin number
	MyRightJoystick.JOYSTICK_HOR=3;

	MyRightJoystick.JOYSTICK_SEL=7; //the push button
    pinMode(MyRightJoystick.JOYSTICK_SEL, INPUT);
	pinMode(MyRightJoystick.JOYSTICK_SEL, INPUT_PULLUP);


	Serial.println("Start caliberating Joyticks.");

	//////Calibrating Left Joystick	
	int tempHoriJoyVal = analogRead(MyLeftJoystick.JOYSTICK_HOR);
	int tempVertiJoyVal = analogRead(MyLeftJoystick.JOYSTICK_VER);

	MyLeftJoystick.JOY_LeftBig = tempHoriJoyVal+300;  //means bigger value is left side
	MyLeftJoystick.JOY_RightLess = tempHoriJoyVal-300;//means less value is right side
	MyLeftJoystick.JOY_UpBig = tempVertiJoyVal+300;   //means bigger value is up
	MyLeftJoystick.JOY_DownLess = tempVertiJoyVal-300;//means less value is down
	
	//////Calibrating Right Joystick	
	tempHoriJoyVal = analogRead(MyRightJoystick.JOYSTICK_HOR);
	tempVertiJoyVal = analogRead(MyRightJoystick.JOYSTICK_VER);

	MyRightJoystick.JOY_LeftBig = tempHoriJoyVal+300;  //means bigger value is left side
	MyRightJoystick.JOY_RightLess = tempHoriJoyVal-300;//means less value is right side
	MyRightJoystick.JOY_UpBig = tempVertiJoyVal+300;   //means bigger value is up
	MyRightJoystick.JOY_DownLess = tempVertiJoyVal-300;//means less value is down


	Serial.println("Caliberation is done.");
}


/**
 * Controlling Servos(Robotic arm) using Joysticks
 * */
int MoveTheRobotUsingJoysticks(int SpeedLevel){ 
	//Reading the Joysticks
	int tempHoriLeftJoyVal = analogRead(MyLeftJoystick.JOYSTICK_HOR);
	int tempVertiLeftJoyVal = analogRead(MyLeftJoystick.JOYSTICK_VER); 	

	int tempHoriRightJoyVal = analogRead(MyRightJoystick.JOYSTICK_HOR);
	int tempVertiRightJoyVal = analogRead(MyRightJoystick.JOYSTICK_VER); 	


	delay(SpeedLevel/5);//speed
	///////////The left Joystick controls servo a and b 
	int step_accurate=2;
	//Horizontal part controls sero a 
	if(tempHoriLeftJoyVal<=MyLeftJoystick.JOY_RightLess){ //Move it to the right
	 	if(MyServoGlobal.servoAngles['a' - 'a']<=180){
			MyServoGlobal.myservo['a' - 'a'].write(MyServoGlobal.servoAngles['a' - 'a']
										=MyServoGlobal.servoAngles['a' - 'a']+step_accurate);
			
			return 1; // to tell user we changed angle
		}
	}  

	
	//Move the servo a         
	if(tempHoriLeftJoyVal>=MyLeftJoystick.JOY_LeftBig){ //Move it to the left  
		if(MyServoGlobal.servoAngles['a' - 'a']>=0){ 
			MyServoGlobal.myservo['a' - 'a'].write(MyServoGlobal.servoAngles['a' - 'a']
										=MyServoGlobal.servoAngles['a' - 'a']-step_accurate);
			return 1; // to tell user we changed angle
		}
	} 

	//Vertical Part controls servo b.  

	if(tempVertiLeftJoyVal>=MyLeftJoystick.JOY_UpBig){  	
 
		if(MyServoGlobal.servoAngles['b' - 'a']>=0){ 
			MyServoGlobal.myservo['b' - 'a'].write(MyServoGlobal.servoAngles['b' - 'a']
										=MyServoGlobal.servoAngles['b' - 'a']-step_accurate);
			return 1; // to tell user we changed angle
		}
	  

	} 


	if(tempVertiLeftJoyVal<=MyLeftJoystick.JOY_DownLess){ 
		    
		if(MyServoGlobal.servoAngles['b' - 'a']<=180){ 
			MyServoGlobal.myservo['b' - 'a'].write(MyServoGlobal.servoAngles['b' - 'a']
										=MyServoGlobal.servoAngles['b' - 'a']+step_accurate);
			return 1; // to tell user we changed angle
		}
	
	}  


	///////////The Right Joystick controls servo c and d 

	//Horizontal part controls sero d 
	if(tempHoriRightJoyVal<=MyRightJoystick.JOY_RightLess){ //Move it to the right

	 	if(MyServoGlobal.servoAngles['d' - 'a']<=180){
			MyServoGlobal.myservo['d' - 'a'].write(MyServoGlobal.servoAngles['d' - 'a']
										=MyServoGlobal.servoAngles['d' - 'a']+step_accurate);
			return 1; // to tell user we changed angle
		}

	}  

	
	//Move the servo d         
	if(tempHoriRightJoyVal>=MyRightJoystick.JOY_LeftBig){ //Move it to the left  

		if(MyServoGlobal.servoAngles['d' - 'a']>=60){ 
			MyServoGlobal.myservo['d' - 'a'].write(MyServoGlobal.servoAngles['d' - 'a']
										=MyServoGlobal.servoAngles['d' - 'a']-step_accurate);								
			return 1; // to tell user we changed angle		
		}
		
	} 

	//Vertical Part controls servo c.  

	if(tempVertiRightJoyVal>=MyRightJoystick.JOY_UpBig){  	
 
		if(MyServoGlobal.servoAngles['c' - 'a']>=0){ 
			MyServoGlobal.myservo['c' - 'a'].write(MyServoGlobal.servoAngles['c' - 'a']
											=MyServoGlobal.servoAngles['c' - 'a']-step_accurate);			
			return 1; // to tell user we changed angle
		}
	  

	} 


	if(tempVertiRightJoyVal<=MyRightJoystick.JOY_DownLess){ 
		    
		if(MyServoGlobal.servoAngles['c' - 'a']<=180){ 
			MyServoGlobal.myservo['c' - 'a'].write(MyServoGlobal.servoAngles['c' - 'a']
											=MyServoGlobal.servoAngles['c' - 'a']+step_accurate);
			return 1; // to tell user we changed angle
		}
	
	}  

	return 0;
}



/************************* Controlling Speed of Robot******************/

typedef struct {
	#define NumOfLED 5
	#define RATING_DIAL 4       // Analog input A4 - changing the speed

	#define RATING_LED_0 2      // rating leds 0-4
	#define RATING_LED_1 3
	#define RATING_LED_2 4
	#define RATING_LED_3 5
	#define RATING_LED_4 6

	#define AnologDemoninator 200	//The maximum return value of analogRea(RATING_DIAL)	 	
									//is about 10000, so 1000/2=5 stars									
									
	int Demoninator;//	Range of analog value is too large
					//	divide this value to rescale the value	
	
 	int Num_LED;
	int SpeedLevel;	
	//LED pins
	int RATING_LED[NumOfLED];  
	int LED_LOW[NumOfLED];   	

}SpeedGlobal;
SpeedGlobal SpeedController;

/**
 * Initialize the Speed Controller, that is, the LEDs for showing
 * speed level and the potentialmeter for changing the speed leve. 
 * */
void InitSpeedController(){
	//Define number of LED	
	SpeedController.Num_LED=NumOfLED;

	//Initial speed
	SpeedController.SpeedLevel=100;
	SpeedController.Demoninator=AnologDemoninator;
		
	//LED pins
	SpeedController.RATING_LED[0]=RATING_LED_0;
	SpeedController.RATING_LED[1]=RATING_LED_1;
	SpeedController.RATING_LED[2]=RATING_LED_2;
	SpeedController.RATING_LED[3]=RATING_LED_3;
	SpeedController.RATING_LED[4]=RATING_LED_4;	

	//////Initialize Rating LEDs
	//Set led pin as output	 
	for(int i=0;i<SpeedController.Num_LED;i++){	  
		pinMode(SpeedController.RATING_LED[i], OUTPUT);       
	}
	
}

/**
 * LED Display the speed level
 * */
void SetLED( int uiOnLED){	
	//Turn off all LEDs
	for(int i=0;i< 5;i++){
		digitalWrite(SpeedController.RATING_LED[i], LOW);
		
	}
	//Turn on the specific LEDs           
	for(int i=0;i< uiOnLED;i++){            	   		      
		digitalWrite(SpeedController.RATING_LED[i], HIGH);                  		
	}

 }  

/**
 * Potential meter control speed
 * */
int AnologControllSpeed(){

	//Reading anologe value
	SpeedController.SpeedLevel = analogRead(RATING_DIAL);
	
	//using the anologe value controll the led
	SetLED(SpeedController.SpeedLevel/SpeedController.Demoninator); // Rating LEDs

	return SpeedController.SpeedLevel;
}

/************************* Moving robot automatically*****************/


/**
 * Controlling Servos automatically.
 * Using the data received from command board to move the 
 * Robotic arm automatically.
 * */

void MoveTheRobotAuto(int SpeedLevel)
{ 
							
	for(int i=0;i<JOINT_ARRAY_SIZE;i++){
							
		SpeedLevel= AnologControllSpeed();		
		for(int i=0;i<SpeedLevel/5;i++){			
			delay(1);//for controlling speed
			
			// Reading command, constantly check if the commander
			//	board is sending some commands.
			if (Serial3.available() > 0){
				int tempsignal = Serial3.read();
				if(tempsignal=='L'){
					Serial.print("------------TERMINATE THE MOVEMENT");
					Serial.println(signal);					
					signal=tempsignal;
					receiveMovementData(&movement1);
					signal='A';			
				
					break ;
				}	
				
				//If we received and command, stop to do the movement
				//Immediately, and quit this functing
				if(tempsignal=='E'||tempsignal=='R'||tempsignal=='F')	
				{
					signal=tempsignal;
				}	
			}

		}
	
		// 200 is the stop flag, once we see a value is 200,
		// It means we should finish the movements.
		// It is just like null terminator in string
		if(movement1.joint1[i]==200)
		{break;}

		Serial.print("Movement #: ");
		Serial.println(i);
		MyServoGlobal.myservo['a' - 'a'].write(movement1.joint1[i]);
		
		MyServoGlobal.myservo['b' - 'a'].write(movement1.joint2[i]);
	
		MyServoGlobal.myservo['c' - 'a'].write(movement1.joint3[i]);
		
		MyServoGlobal.myservo['d' - 'a'].write(movement1.joint4[i]);
		
	}		
	
}

/************************* Recording Movements*************************/

/**
 * Recording the change of angles for 4 servos of the robotic arm
 * */
int recordingMovement(){
	//SerialControllingServos() ;  
	int speed= AnologControllSpeed();
	
	if(MoveTheRobotUsingJoysticks(speed)){// if we have changed any angles, record it

		if(MyServoGlobal.servoAngles['a' - 'a']<=0) MyServoGlobal.servoAngles['a' - 'a']=5;
		if(MyServoGlobal.servoAngles['b' - 'a']<=0) MyServoGlobal.servoAngles['b' - 'a']=5;
		if(MyServoGlobal.servoAngles['c' - 'a']<=0) MyServoGlobal.servoAngles['c' - 'a']=5;
		if(MyServoGlobal.servoAngles['d' - 'a']<=0) MyServoGlobal.servoAngles['d' - 'a']=5;

		if(MyServoGlobal.servoAngles['a' - 'a']>=180) MyServoGlobal.servoAngles['a' - 'a']=175;
		if(MyServoGlobal.servoAngles['b' - 'a']>=180) MyServoGlobal.servoAngles['b' - 'a']=175;
		if(MyServoGlobal.servoAngles['c' - 'a']>=180) MyServoGlobal.servoAngles['c' - 'a']=175;
		if(MyServoGlobal.servoAngles['d' - 'a']>=180) MyServoGlobal.servoAngles['d' - 'a']=175;
 

		movement1.joint1[NumJoinArrayLength]=MyServoGlobal.servoAngles['a' - 'a'];
		movement1.joint2[NumJoinArrayLength]=MyServoGlobal.servoAngles['b' - 'a'];
		movement1.joint3[NumJoinArrayLength]=MyServoGlobal.servoAngles['c' - 'a'];
		movement1.joint4[NumJoinArrayLength]=MyServoGlobal.servoAngles['d' - 'a'];
		NumJoinArrayLength++;

		
		
		return NumJoinArrayLength;// If recorded one time, return number of total times
	}


	return 0;// If did recorded, return 0
}


/**
 * 	FinishRecording: To detect if we pushed the OK button 
 * 	Once we pushed it, it stops recording the movements		 
 * */

int FinishRecording(){
	static int uiButtonTimes=3;

	//Detecting button
	 if(digitalRead(MyRightJoystick.JOYSTICK_SEL)==0){		
         while(digitalRead(MyRightJoystick.JOYSTICK_SEL)==0) { delay(300);  }
	     uiButtonTimes++;             
		Serial.println("Pushed ");          	 		 		
	}

	
	//If button not bushed, continue the recording          
	 
	if (uiButtonTimes%2) {//Mode 0 
		if(int a=recordingMovement()){  //if recorded, print it  
			Serial.print("Recorded times: ");
			Serial.println(a);
		}
	
	
	} 


    //If button bushed, finishe the recording & prepare to communicate

	if (!(uiButtonTimes%2) ) { // If button  bushed Mode 1		
		Serial.println("Finished Recording. ");

		//The terminal signal
		movement1.joint1[NumJoinArrayLength]=200;
		movement1.joint2[NumJoinArrayLength]=200;
		movement1.joint3[NumJoinArrayLength]=200;
		movement1.joint4[NumJoinArrayLength]=200;
		NumJoinArrayLength=0;
		 uiButtonTimes++;
		return 1;

	}	
	return 0;

}



void setup()
{
	Serial.begin(9600);
	Serial3.begin(9600);
	InitServos();	
	InitJoysticks();
	InitSpeedController();
}


void loop()
{      
	// Reading command from PC
	if (Serial.available() > 0){
		int tempsignal = Serial.read();
		if(tempsignal=='E'||tempsignal=='R'||tempsignal=='F'||tempsignal=='L'){
			Serial.print("-----------------------");
			Serial.println(signal);		
			
			signal=tempsignal;
		}			
	}
	
	// Reading command from commander board
	if (Serial3.available() > 0){
		int tempsignal = Serial3.read();
		if(tempsignal=='E'||tempsignal=='R'||tempsignal=='F'||tempsignal=='L'){
			Serial.print("-----------------------");							
			signal=tempsignal;		
			Serial.println(signal);	
		}			
	}
	
	//Analyzing the commands
	switch (signal){ 
		
		case	'E'://'E' stands for excute the movements
			{		
								
			int speed= AnologControllSpeed();
			MoveTheRobotAuto(speed);
			Serial.print("Received E, Excute! ");
			break;
			}
		case    'L':// loading movement data from commander board
			{
			receiveMovementData(&movement1);
			signal='A';
			break;
			}
		case	'R': // Start to recording the movements
			{
				{
					Serial.println("I received R");	
					if(FinishRecording()){// if recording is finished, 
									//send the data to commander board	
			
						Serial3.write('R');
						delay(100);
						printDataRead(&movement1);
			
						//Send the data to be saved in the Sd Card
						sendMovementData(&movement1);
						signal='A';
						Serial.println("Command recorded and sent successfully");

						Serial.println(signal);
																														
						delay(50);	// put a delay to make sure the commander
									//	did not loose and feedback from this board										
						Serial.println("Command Executed successfully");
					}
					break;
				}
	
							}

		case	'F':// In free mode, we can move the robotic arm
					//but does not recoding the movements 
			{

				Serial3.write('S');

				int speed= AnologControllSpeed();
				MoveTheRobotUsingJoysticks(speed);
				Serial.print(signal);
				break;				
			}
				
	}

}
 


