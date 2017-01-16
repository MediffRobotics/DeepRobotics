
#include <Servo.h>
/*****************************For controlling Servos*******************/

typedef struct {
#define NUM_SERVOS 3
  //For servos  
  int numServos;
  int servoPins[NUM_SERVOS];
  int servoAngles[NUM_SERVOS];// Stands for servo a-d
  Servo myservo[NUM_SERVOS];
  int pos;
  int MaxChars;   // an int string contains up to 5 digits and is terminated 
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
  MyServoGlobal.servoPins[0] = 3;// servos on pins 8 through 11
  MyServoGlobal.servoPins[1] = 5;// servos on pins 8 through 11
  MyServoGlobal.servoPins[2] = 6;// servos on pins 8 through 11
 
  MyServoGlobal.myservo;
  MyServoGlobal.pos =0;
  MyServoGlobal.MaxChars = 2; // an int string contains up to 5 
                //digits and is terminated by a 0 to
                // indicate end of string
  MyServoGlobal.strValue;   // must be big enough for digits and terminating null
  MyServoGlobal.index = 0; // the index into the array storing the received digits
  
  //Initialize the hardwares  
  
  for(int i=0; i < MyServoGlobal.numServos; i++){
  MyServoGlobal.myservo[i].attach(MyServoGlobal.servoPins[i]);}

    //Initiate servos' positing 
    
    MyServoGlobal.servoAngles['a' - 'a']=110;
    MyServoGlobal.servoAngles['b' - 'a']=20;
    MyServoGlobal.servoAngles['c' - 'a']=100;
   

    MyServoGlobal.myservo['a' - 'a'].write(MyServoGlobal.servoAngles['a' - 'a']);
    MyServoGlobal.myservo['b' - 'a'].write(MyServoGlobal.servoAngles['b' - 'a']);
    MyServoGlobal.myservo['c' - 'a'].write(MyServoGlobal.servoAngles['c' - 'a']);
   
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
        
      } // is 'a' letter for our servos?
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





void setup()
{
  Serial.begin(9600);

  InitServos(); 


}


void loop()
{      
 
  SerialControllingServos();
  

}
 



