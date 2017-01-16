#include <MsTimer2.h>

// the setup function runs once when you press reset or power the board
const int CP =  5;      
const int DIR =  4;      
//const int ENA =  13;      
volatile int StepCounter=0;
volatile bool DirectionFlag=0;
void setup() {
  // initialize digital pin 13 as an output.
  //pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);  
    

  pinMode(CP,OUTPUT);
 // MsTimer2::set(0,TimerStepperControl);
 // MsTimer2::start();


}

// the loop function runs over and over again forever
void loop() {
   //digitalWrite(ENA, HIGH);

  
   DelayStepperControl();

    
              
}

void TimerStepperControl(){
  static boolean output=HIGH;
  //Direction
  if(StepCounter%500==0){    
    DirectionFlag=!DirectionFlag;
    digitalWrite(DIR, DirectionFlag);
    }    
  StepCounter++;  
  
  digitalWrite(CP,output);
  output=!output;
  }


void DelayStepperControl(){
  for(int i=1;i<=5000;i++){
  digitalWrite(DIR, LOW);
  
    
  digitalWrite(CP, LOW);    
  delayMicroseconds(1000);

  digitalWrite(CP, HIGH);    
  delayMicroseconds(1000);
      
    }

/*
  for(int i=1;i<=5000;i++){
  digitalWrite(DIR, HIGH);
  
    
  digitalWrite(CP, LOW);    
  delayMicroseconds(1000);

  digitalWrite(CP, HIGH);    
  delayMicroseconds(1000);
      
    }
    
    */
  
  }

