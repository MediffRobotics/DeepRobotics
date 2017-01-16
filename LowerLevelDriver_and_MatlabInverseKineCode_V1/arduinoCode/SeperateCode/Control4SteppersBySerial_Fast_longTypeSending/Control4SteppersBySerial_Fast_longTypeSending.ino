
#include <Servo.h>
#include <math.h>

/********************SERIAL BUFFER**********************************/
/******************************************************/
//a buffer to save digits
const int MaxChars=8;   // an int string contains up to 8 digits and is terminated 
char strValue[MaxChars]; // must be big enough for digits and terminating null
int strValueIndex=0 ; // the index into the array storing the received digits

long lon_ReceivedMotorData=0;  
long signedReceivedVale=1;
 
/*******************Timmer setup**********************/
/****************************************************/
#define bbs(x)  (1<<x)
 // Microstep=16; 1.8deg per step, one revolution = 3200steps 
 // one revolution = 8mm. 3200 steps=8mm. 
 // one timer tick = 1/2 period => 800 ticks per mm

// Prescaler = 64
//16Mhz/64=0.25Mhz 1/0.25=4us 4*10=40us => 
const uint8_t myTOP = 20;
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


///// Interrupt Service Routine for TIMER2
ISR(TIMER2_COMPA_vect)
{
 
  //test_AxisRotateStepper_ISR();
 AxisRotateStepper_ISR(); 

  ElbowRotateGivenSteps_ISR();
  UpperArmStepper_ISR();
  
  ROTATE_BASEStepper_ISR();
}




/*******************STEPPERS SETUP*****************/
/**************************************************/


/*****************Stepper controls****************/



typedef struct {
#define NUM_STEPPERS 3
  //For steppers
  int stepperPins[NUM_STEPPERS];
  long stepperSteps[NUM_STEPPERS];// Stands for servo a-d
                    
}StepperGlobal;
StepperGlobal MyStepper;

void InitSteppers(){
  for(int i=0; i < NUM_STEPPERS; i++){
    MyStepper.stepperSteps[i]=0;
  }
}


/*************for stepper****************/

////////Axis rotate stepper

const int CP_AIXS =  12;     
const int DIR_AIXS =  8;      
const int ENA_AIXS =  2;      

volatile long StepCounter_AXIS=0;
volatile bool DirectionFlag_AXIS=1;
volatile long AxisRotate_TotalSteps=0;
volatile bool AxisMotor_WorkingFlag=false;
volatile bool sentFlag_Axis=false;

////////////////////////rotate stepper routine
void setup_rotateStepper(){
  pinMode(ENA_AIXS, OUTPUT);
  pinMode(DIR_AIXS, OUTPUT);  
  pinMode(CP_AIXS,OUTPUT);
  digitalWrite(ENA_AIXS, HIGH);

}

//Axis rotation RotateGivenSteps
void Axis_RotateGivenSteps( long steps,bool Step_direction){
 
    AxisMotor_WorkingFlag=true;
  DirectionFlag_AXIS=Step_direction; 
  AxisRotate_TotalSteps=steps;
    
  }
  
//axis Rotate ISR 
void AxisRotateStepper_ISR(){
  static boolean outputPulse=HIGH;
  
  digitalWrite(DIR_AIXS, DirectionFlag_AXIS);  //Determin direction
  
  //determing the task is finished,yes,reset variables
  if((StepCounter_AXIS==AxisRotate_TotalSteps)||(AxisMotor_WorkingFlag==false)){    
   if((StepCounter_AXIS==AxisRotate_TotalSteps)&&(AxisRotate_TotalSteps!=0)){
     sentFlag_Axis=true;
     }
     
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

////////////Axis Rotate back and force
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

/*********elbow stepper****************/
volatile  long StepCounter_ELBOW=0;
volatile bool DirectionFlag_ELBOW=0;
volatile long elbowStepper_TotalSteps=0;
volatile bool elbowStepper_WorkingFlag=false;
volatile bool sentFlag_Elbow=false;

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


void ElbowRotateGivenSteps( long TargetSteps,bool Step_direction){        
      

      elbowStepper_WorkingFlag=true; 
  
      elbowStepper_TotalSteps=TargetSteps;
      DirectionFlag_ELBOW=Step_direction;           
                                        
     
      }


void ElbowRotateGivenSteps_ISR(){
   static boolean outputPulse=HIGH;   //for generating pulses            
      
      if((StepCounter_ELBOW==elbowStepper_TotalSteps)||(elbowStepper_WorkingFlag==false)){    

        if((StepCounter_ELBOW==elbowStepper_TotalSteps)&&(elbowStepper_TotalSteps!=0)){
          sentFlag_Elbow=true;
        }        
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


/************UPPER ARM STEPPER SETUP****************/
// To indicate if stepper is working. 
// If yes, True ; otherwise, False

volatile  long StepCounter_UPARM=0;
volatile bool DirectionFlag_UPARM=0;
volatile  long uparmStepper_TotalSteps=0;
volatile bool uparmStepper_WorkingFlag=false;
volatile  static bool sentFlag_Uparm=false; //checking sent signal

const int CP_UpArm  =  13;      
const int DIR_UpArm =  10;      
const int ENA_UpArm =  14;

// setting UpArm stepper driver
void setup_UpArmStepper(){
  pinMode(ENA_UpArm, OUTPUT);
  pinMode(DIR_UpArm, OUTPUT);  
  pinMode(CP_UpArm,OUTPUT);
  
  digitalWrite(ENA_UpArm, HIGH);  
  }
  
  
void UpperArmGivenSteps( long steps,bool Step_direction){
  

  uparmStepper_WorkingFlag=true;
  DirectionFlag_UPARM=Step_direction; 
  uparmStepper_TotalSteps=steps;
  

    
  }
  
  
  void UpperArmStepper_ISR(){
  static boolean outputPulse=HIGH;
  
  digitalWrite(DIR_UpArm, DirectionFlag_UPARM);  //Determin direction
  
  //determing the task is finished,yes,reset variables
  if((StepCounter_UPARM==uparmStepper_TotalSteps)||(uparmStepper_WorkingFlag==false)){    
    
   if((StepCounter_UPARM==uparmStepper_TotalSteps)&&(uparmStepper_TotalSteps!=0)){
   sentFlag_Uparm=true;
   }
   
   
    //Reset parameters
    StepCounter_UPARM=0;    
    uparmStepper_TotalSteps=0;
    uparmStepper_WorkingFlag=false;
   
    return; // task finished
    }
  
  // if not finished task, flip output
  uparmStepper_WorkingFlag=true; // to indicate the stepper is still working   
 // sentFlag_Uparm=false;
  StepCounter_UPARM++; 
  digitalWrite(CP_UpArm,outputPulse);
  outputPulse=!outputPulse;
  }  
 /************BASE STEPPER SETUP****************/
// To indicate if stepper is working. 
// If yes, True ; otherwise, False

volatile  long StepCounter_ROTATE_BASE=0;
volatile bool DirectionFlag_ROTATE_BASE=0;
volatile  long ROTATE_BASEStepper_TotalSteps=0;
volatile bool ROTATE_BASEStepper_WorkingFlag=false;
volatile  static bool sentFlag_ROTATE_BASE=false; //checking sent signal

const int CP_ROTATE_BASE  =  17;      
const int DIR_ROTATE_BASE =  16;      
const int ENA_ROTATE_BASE =  15;

// setting ROTATE_BASE stepper driver
void setup_ROTATE_BASEStepper(){
  pinMode(ENA_ROTATE_BASE, OUTPUT);
  pinMode(DIR_ROTATE_BASE, OUTPUT);  
  pinMode(CP_ROTATE_BASE,OUTPUT);
  digitalWrite(ENA_ROTATE_BASE, HIGH);
  /*
  digitalWrite(ENA_ROTATE_BASE, LOW);  
  digitalWrite(DIR_ROTATE_BASE, LOW);
  digitalWrite(CP_ROTATE_BASE, LOW);
*/  
}
  
  
void ROTATE_BASEArmGivenSteps( long steps,bool Step_direction){
  

  ROTATE_BASEStepper_WorkingFlag=true;
  DirectionFlag_ROTATE_BASE=Step_direction; 
  ROTATE_BASEStepper_TotalSteps=steps;
  

    
  }
  
  
  void ROTATE_BASEStepper_ISR(){
  static boolean outputPulse=HIGH;
  
  digitalWrite(DIR_ROTATE_BASE, DirectionFlag_ROTATE_BASE);  //Determin direction
  
  //determing the task is finished,yes,reset variables
  if((StepCounter_ROTATE_BASE==ROTATE_BASEStepper_TotalSteps)||(ROTATE_BASEStepper_WorkingFlag==false)){    
    
   if((StepCounter_ROTATE_BASE==ROTATE_BASEStepper_TotalSteps)&&(ROTATE_BASEStepper_TotalSteps!=0)){
   sentFlag_ROTATE_BASE=true;
   }
   
   
    //Reset parameters
    StepCounter_ROTATE_BASE=0;    
    ROTATE_BASEStepper_TotalSteps=0;
    ROTATE_BASEStepper_WorkingFlag=false;
   
    return; // task finished
    }
  
  // if not finished task, flip output
  ROTATE_BASEStepper_WorkingFlag=true; // to indicate the stepper is still working   
 // sentFlag_ROTATE_BASE=false;
  StepCounter_ROTATE_BASE++; 
  digitalWrite(CP_ROTATE_BASE,outputPulse);
  outputPulse=!outputPulse;
  }  






 
/*****************************For controlling Servos*******************/
/*********************************************************************/

typedef struct {
#define NUM_SERVOS 3
  //For servos  
  int numServos;
  int servoPins[NUM_SERVOS];
  int servoAngles[NUM_SERVOS];// Stands for servo a-d
  Servo myservo[NUM_SERVOS];
  long pos;
  
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
 
  MyServoGlobal.myservo;
  MyServoGlobal.pos =0;

 
  
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

//////////////////////////////////////////////

void ControlServosBySerial(char ch){
                             
      // use atoi to convert the string to an int 
      MyServoGlobal.pos = convStrToLong();                                   
      MyServoGlobal.myservo[ch - 'a'].write(MyServoGlobal.pos); 
      //reset string
      
      //Serial.print(MyServoGlobal.pos);
      Serial.println(ch); 
}

//Converting string to long
long convStrToLong(){
      long   output_val;
  //converting to long
      unsigned int maxIndex=strValueIndex-1;
      for(int i=0;i<=maxIndex;i++){
        //Serial.println(strValue[i]-'0');  
        lon_ReceivedMotorData=pow(10,maxIndex-i )*double(strValue[i]-'0')+lon_ReceivedMotorData;
      }
      lon_ReceivedMotorData=signedReceivedVale*lon_ReceivedMotorData;
      
    //  Serial.println(lon_ReceivedMotorData);

      output_val=lon_ReceivedMotorData;      
      //reseting params
      signedReceivedVale=1;
      lon_ReceivedMotorData=0;   
      strValueIndex=0;
      for (int i=0;i<MaxChars;i++){
        strValue[i]=' ';
        }
          
  
  return output_val;
}


/***********serial communication*******************/
/**************************************************/
void SerialCommunication(){      
  if( Serial.available())
    {          
      char ch = Serial.read();
      if(strValueIndex <= 
          MaxChars && ch >= '0' && ch <= '9'){     
         
            
          // add the ASCII character to the string;
          strValue[strValueIndex++] = ch; 
       }
       else if(ch=='-'||ch=='+'){
            if(ch=='-'){
            signedReceivedVale=-1;
            }
            else{
            signedReceivedVale=1;            
            }                        
      }                      
      else if(ch >= 'a' && ch <= 'a'+ MyServoGlobal.numServos) {   
       // converting to long type
            
         ControlServosBySerial(ch);              
          
      }else if(ch >= 'e'&& ch<='e'+NUM_STEPPERS ) {
        ControlSteppersBySerial(ch);
        //go to stepper control program          
    }                  
      
   }
}




void setup()
{
  Serial.begin(1200);
  InitServos();     
  
  setMyTimer2( );
  
  //INIT DRIVER WIRES
  setup_ElbowStepper();
  //INIT rotate stepper
  setup_rotateStepper();
  //Setup UpperArmStepper
  setup_UpArmStepper();
  
  //setup rotate base
  setup_ROTATE_BASEStepper();
  // Testing demo



}


void loop()
{       
  SerialCommunication();  
  StepperWorkingCheck();
}
 

/*************for stepper****************/

//if finished working,send serial a flag
void StepperWorkingCheck(){
  if(sentFlag_ROTATE_BASE==true){
     sentFlag_ROTATE_BASE=false;
     Serial.println('eeeee');  // tell pc end, the task is done
     //delay(10);
   }
  
  //upper arm 
 
   if(sentFlag_Uparm==true){
     sentFlag_Uparm=false;
     Serial.println('fffff');  // tell pc end, the task is done
     //delay(10);
   }
   
   if(sentFlag_Elbow==true){
     sentFlag_Elbow=false;
     Serial.println('ggggg');  // tell pc end, the task is done
     //delay(10);
   }
   
      if(sentFlag_Axis==true){
     sentFlag_Axis=false;
     Serial.println('hhhhh');  // tell pc end, the task is done
    // delay(10);
   }

   }


// serial control steppers
void ControlSteppersBySerial(char ch){  
      bool s_direction=0;
      // use atoi to convert the string to an int 
       
      long numSteps = convStrToLong();                                   
      
      if(numSteps>0){
        s_direction=1;
      }else{
        s_direction=0;      
      } 
      numSteps=abs(numSteps);
      
      if(ch=='e'){
         ROTATE_BASEArmGivenSteps( numSteps,s_direction);
      } 
      // To do: adding stepper control functions
      if(ch=='f'){
      UpperArmGivenSteps(numSteps,s_direction);

      }
      if(ch=='g'){
         ElbowRotateGivenSteps(numSteps,s_direction);
      }
      
      if(ch=='h'){
         Axis_RotateGivenSteps(numSteps,s_direction);
      }
      
       
}
