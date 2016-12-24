#include <MsTimer2.h>

// the setup function runs once when you press reset or power the board
const int CP_AIXS =  11;     
const int DIR_AIXS =  7;      
const int ENA_AIXS =  4;      
volatile int StepCounter_AXIS=0;
volatile bool DirectionFlag_AXIS=0;

void setup_rotateStepper(){
  pinMode(ENA_AIXS, OUTPUT);
  pinMode(DIR_AIXS, OUTPUT);  
  pinMode(CP_AIXS,OUTPUT);
  MsTimer2::set(0,TimerStepperControl);
  MsTimer2::start();
}
void setup() {
  

setup_rotateStepper();

}

// the loop function runs over and over again forever
void loop() {
   digitalWrite(ENA_AIXS, HIGH);

  
  

    
              
}

void TimerStepperControl(){
  static boolean output_AXIS=HIGH;
  //Direction
  if(StepCounter_AXIS%5000==0){    
    DirectionFlag_AXIS=!DirectionFlag_AXIS;
    digitalWrite(DIR_AIXS, DirectionFlag_AXIS);
    }    
  StepCounter_AXIS++;  
  
  digitalWrite(CP_AIXS,output_AXIS);
  output_AXIS=!output_AXIS;
  }


void DelayStepperControl(){
  for(int i=1;i<=500;i++){
  digitalWrite(DIR_AIXS, LOW);
  
    
  digitalWrite(CP_AIXS, LOW);    
  delayMicroseconds(1000);

  digitalWrite(CP_AIXS, HIGH);    
  delayMicroseconds(1000);
      
    }


  for(int i=1;i<=1000;i++){
  digitalWrite(DIR_AIXS, HIGH);
  
    
  digitalWrite(CP_AIXS, LOW);    
  delayMicroseconds(1000);

  digitalWrite(CP_AIXS, HIGH);    
  delayMicroseconds(1000);
      
    }
  
  }


