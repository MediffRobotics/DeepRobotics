
#include <Servo.h>
//a buffer to save digits
const int MaxChars=6;   // an int string contains up to 5 digits and is terminated 
char strValue[MaxChars]; // must be big enough for digits and terminating null
 int strValueIndex=0 ; // the index into the array storing the received digits
/*****************************For controlling Servos*******************/

typedef struct {
#define NUM_SERVOS 4
  //For servos  
  int numServos;
  int servoPins[NUM_SERVOS];
  int servoAngles[NUM_SERVOS];// Stands for servo a-d
  Servo myservo[NUM_SERVOS];
  int pos;
  
          //by a 0 to indicate end of string                     
}ServoGlobal;
ServoGlobal MyServoGlobal;

/**
 * Initialize Servos
 * */
void InitServos(){
  
  //Initialize the global variables
  
  MyServoGlobal.numServos=NUM_SERVOS; 
  MyServoGlobal.servoPins[0] = 3;// servos on pins 
  MyServoGlobal.servoPins[1] = 5;// servos on pins 
  MyServoGlobal.servoPins[2] = 6;// servos on pins 
  MyServoGlobal.servoPins[3] = 9;// servos on pins 
 
  MyServoGlobal.myservo;
  MyServoGlobal.pos =0;

 
  
  //Initialize the hardwares  
  
  for(int i=0; i < MyServoGlobal.numServos; i++){
  MyServoGlobal.myservo[i].attach(MyServoGlobal.servoPins[i]);}

    //Initiate servos' positing 
    
    MyServoGlobal.servoAngles['a' - 'a']=110;
    MyServoGlobal.servoAngles['b' - 'a']=20;
    MyServoGlobal.servoAngles['c' - 'a']=100;
     MyServoGlobal.servoAngles['d' - 'a']=100;

    MyServoGlobal.myservo['a' - 'a'].write(MyServoGlobal.servoAngles['a' - 'a']);
    MyServoGlobal.myservo['b' - 'a'].write(MyServoGlobal.servoAngles['b' - 'a']);
    MyServoGlobal.myservo['c' - 'a'].write(MyServoGlobal.servoAngles['c' - 'a']);
    MyServoGlobal.myservo['d' - 'a'].write(MyServoGlobal.servoAngles['d' - 'a']);
}


typedef struct {
#define NUM_STEPPERS 3
  //For steppers
  int stepperPins[NUM_STEPPERS];
  int stepperSteps[NUM_STEPPERS];// Stands for servo a-d
                    
}StepperGlobal;
StepperGlobal MyStepper;

void InitSteppers(){
  for(int i=0; i < NUM_STEPPERS; i++){
    MyStepper.stepperSteps[i]=0;
  }
}

//////////////////////////////////////////////

void ControlServosBySerial(char ch){
                             
      // use atoi to convert the string to an int 
      MyServoGlobal.pos = atoi(strValue);                                   
      MyServoGlobal.myservo[ch - 'a'].write(MyServoGlobal.pos); 
      //reset string
      strValueIndex=0;
      for (int i=0;i<MaxChars;i++){
        strValue[i]=' ';
        }
      
      Serial.print(MyServoGlobal.pos);
      Serial.println(ch); 
}

/*************for stepper****************/
/****************************************/
void ControlSteppersBySerial(char ch){  
      
      // use atoi to convert the string to an int 
      int numSteps = atoi(strValue);                                   
       
      // To do: adding stepper control functions
      
      //reset string
      strValueIndex=0;
      for (int i=0;i<MaxChars;i++){
      strValue[i]=' ';
      }
      
      Serial.print(numSteps);
      Serial.println(ch); 
  
  
}

/**
 * Controlling Servos using serial port
 * */

void SerialCommunication(){
  //Todo: checking if finished tasks
  
  
  if( Serial.available())
    {          
      char ch = Serial.read();
      if(strValueIndex <= 
          MaxChars && ch >= '0' && ch <= '9'||ch=='-'||ch=='+'){            
          // add the ASCII character to the string;
          strValue[strValueIndex++] = ch; 
          
       } else if(ch >= 'a' && ch <= 'a'+ MyServoGlobal.numServos) {      
         ControlServosBySerial(ch);              
          
      }else if(ch >= 'f'&& ch<='f'+NUM_STEPPERS ) {
        ControlSteppersBySerial(ch);
        //go to stepper control program
          
    }                  
      
   }
}





void setup()
{
  Serial.begin(9600);

  InitServos(); 


}


void loop()
{      
 
  SerialCommunication();
  

}
 



