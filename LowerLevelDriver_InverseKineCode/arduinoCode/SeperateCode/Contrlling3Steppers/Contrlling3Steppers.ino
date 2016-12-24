#include <math.h>
////////////////////////////////////TIMMER SETUP
#define bbs(x)  (1<<x)
 // Microstep=16; 1.8deg per step, one revolution = 3200steps 
 // one revolution = 8mm. 3200 steps=8mm. 
 // one timer tick = 1/2 period => 800 ticks per mm

// Prescaler = 64
//16Mhz/64=0.25Mhz 1/0.25=4us 4*10=40us => 
const uint8_t myTOP = 39;



/************ROTATE STEPPER SETUP****************/
/************************************************/
/////////////////////////////////
// the setup function runs once when you press reset or power the board
const int CP_AIXS =  12;     
const int DIR_AIXS =  8;      
const int ENA_AIXS =  2;      

volatile unsigned long StepCounter_AXIS=0;
volatile bool DirectionFlag_AXIS=1;
volatile unsigned long AxisRotate_TotalSteps=0;
volatile bool AxisMotor_WorkingFlag=true;

// To indicate if stepper is working. 
// If yes, True ; otherwise, False

volatile unsigned long StepCounter_UPARM=0;
volatile bool DirectionFlag_UPARM=0;
volatile unsigned long uparmStepper_TotalSteps=0;
volatile bool uparmStepper_WorkingFlag=true;

////////////////////////rotate stepper routine
void setup_rotateStepper(){
  pinMode(ENA_AIXS, OUTPUT);
  pinMode(DIR_AIXS, OUTPUT);  
  pinMode(CP_AIXS,OUTPUT);
  digitalWrite(ENA_AIXS, HIGH);

}


/************ELBOW STEPPER SETUP****************/
/************************************************/
volatile unsigned long StepCounter_ELBOW=0;
volatile bool DirectionFlag_ELBOW=0;
volatile unsigned long elbowStepper_TotalSteps=0;
volatile bool elbowStepper_WorkingFlag=true;

const int CP_ELBOW =  11;     
const int DIR_ELBOW =  7;      
const int ENA_ELBOW =  4; 
// setting elbow stepper driver
void setup_ElbowStepper(){
  pinMode(ENA_ELBOW, OUTPUT);
  pinMode(DIR_ELBOW, OUTPUT);  
  pinMode(CP_ELBOW,OUTPUT);
  digitalWrite(ENA_ELBOW, HIGH);  
  
  }


////////////Rotate back and force
void test_AxisRotateStepper_ISR(){
  static boolean outputPulse=LOW;
  //Direction
  if(StepCounter_AXIS%50000==0){    
    DirectionFlag_AXIS=!DirectionFlag_AXIS;
    digitalWrite(DIR_AIXS, DirectionFlag_AXIS);
    }    
  StepCounter_AXIS++;  
  
  digitalWrite(CP_AIXS,outputPulse);
  outputPulse=!outputPulse;
  }
 /************UPPER ARM STEPPER SETUP****************/
/************************************************/


const int CP_UpArm  =  13;      
const int DIR_UpArm =  10;      
const int ENA_UpArm =  14;



// setting elbow stepper driver
void setup_UpArmStepper(){
  pinMode(ENA_UpArm, OUTPUT);
  pinMode(DIR_UpArm, OUTPUT);  
  pinMode(CP_UpArm,OUTPUT);
  
  digitalWrite(ENA_UpArm, HIGH);  
  }
  
  
//**************************************************
//**************************************************

///// Interrupt Service Routine for TIMER2
ISR(TIMER2_COMPA_vect)
{
 
  //test_AxisRotateStepper_ISR();
  AxisRotateStepper_ISR();

  ElbowRotateGivenSteps_ISR();
  UpperArmStepper_ISR();
}

void setup( ) {    
  Serial.begin(9600);  
  
  setMyTimer2( );
  
  //INIT DRIVER WIRES
  setup_ElbowStepper();
  ElbowRotateGivenSteps(30000,1);
  
  //INIT rotate stepper
  setup_rotateStepper();
  Axis_RotateGivenSteps(30000,1);
  //Setup UpperArmStepper
  setup_UpArmStepper();
  UpperArmGivenSteps(30000,1);

}


bool SettingALLSteppersSteps(float UpperArm, float UpperArmAxis,float Elbow){
  //If task finished, return true. otherwise false
  
  AxisMotor_WorkingFlag=true; // axis stepper rotation
  Axis_RotateGivenSteps(UpperArmAxis,1);  
  ElbowRotateGivenSteps(Elbow,0);

  //wait untile all motors finished
  while(AxisMotor_WorkingFlag==true||elbowStepper_WorkingFlag==true){ 
              
   }  
  
  }





void loop() {  
  Serial.println(StepCounter_AXIS);
  Serial.println(StepCounter_ELBOW);
  Serial.println("________");
}


/********Axis rotation stepper*****/
/*********************************/
void Axis_RotateGivenSteps(unsigned long steps,bool direction){
 
  DirectionFlag_AXIS=direction; 
  AxisRotate_TotalSteps=steps;
    
  }


//Rotate ISR 
void AxisRotateStepper_ISR(){
  static boolean outputPulse=HIGH;
  
  digitalWrite(DIR_AIXS, DirectionFlag_AXIS);  //Determin direction
  
  //determing the task is finished,yes,reset variables
  if((StepCounter_AXIS==AxisRotate_TotalSteps)||(AxisMotor_WorkingFlag==false)){    
    
    //Reset parameters
    StepCounter_AXIS=0;    
    AxisRotate_TotalSteps=0;
    AxisMotor_WorkingFlag=false;
    return; // task finished
    }
  
  // if not finished task, flip output
  AxisMotor_WorkingFlag=true; // to indicate the stepper is still working   
  StepCounter_AXIS++; 
  digitalWrite(CP_AIXS,outputPulse);
  outputPulse=!outputPulse;
  }

/******************Elbow Stepper**************/
/*********************************************/

void ElbowRotateGivenSteps(unsigned long TargetSteps,bool Direction){                                             
      elbowStepper_TotalSteps=TargetSteps;
      DirectionFlag_ELBOW=Direction;           
                                        
     
      }



void ElbowRotateGivenSteps_ISR(){
   static boolean outputPulse=HIGH;   //for generating pulses            
      
      if((StepCounter_ELBOW==elbowStepper_TotalSteps)||(elbowStepper_WorkingFlag==false)){                          
        // If reach the target, reset all
        StepCounter_ELBOW=0;
        elbowStepper_TotalSteps=0;                       
        elbowStepper_WorkingFlag=false;// indicate stop working
        return;
        }
  
        elbowStepper_WorkingFlag=true;// indicate still working         
        digitalWrite(DIR_ELBOW, DirectionFlag_ELBOW);           
        StepCounter_ELBOW++;    
        digitalWrite(CP_ELBOW,outputPulse);
        outputPulse=!outputPulse;              
  }

  //////////////////////////////////////upper arm 
  void UpperArmGivenSteps(unsigned long steps,bool direction){
 
  DirectionFlag_UPARM=direction; 
  uparmStepper_TotalSteps=steps;
    
  }
  void UpperArmStepper_ISR(){
  static boolean outputPulse=HIGH;
  
  digitalWrite(DIR_UpArm, DirectionFlag_UPARM);  //Determin direction
  
  //determing the task is finished,yes,reset variables
  if((StepCounter_UPARM==uparmStepper_TotalSteps)||(uparmStepper_WorkingFlag==false)){    
    
    //Reset parameters
    StepCounter_UPARM=0;    
    uparmStepper_TotalSteps=0;
    uparmStepper_WorkingFlag=false;
    return; // task finished
    }
  
  // if not finished task, flip output
  uparmStepper_WorkingFlag=true; // to indicate the stepper is still working   
  StepCounter_UPARM++; 
  digitalWrite(CP_UpArm,outputPulse);
  outputPulse=!outputPulse;
  }

/******************TIMMER2*********************/
/*********************************************/

void setMyTimer2( ){
  cli();  // 禁止中斷
  TCCR2A = bbs(WGM21);  // CTC mode 2; Clear Timer on Compare, see p.158-162
  TCCR2B = bbs(CS22);  // Prescaler == 64; see p.162 in datasheet 
  ///// 注意 WGM22 在 TCCR2B, 但 WGM21 與 WGM20 在 TCCR2A; 
  ///// mode 由 WGM22, WGM21, WGM20 決定 (see datasheet p.158-162)
  OCR2A = myTOP;  // TOP count for CTC, 與 prescaler 有關
  TCNT2=0;  // counter 歸零 
  TIMSK2 |= bbs(OCIE2A);  // enable CTC for TIMER2_COMPA_vect
  sei();  // 允許中斷
}




