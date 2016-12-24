/********************SERIAL BUFFER**********************************/
/******************************************************************/
//a buffer to save digits
const int MaxChars=8;   // an int string contains up to 8 digits and is terminated 
char strValue[MaxChars]; // must be big enough for digits and terminating null
int strValueIndex=0 ; // the index into the array storing the received digits
long lon_ReceivedMotorData=0;  
long signedReceivedVale=1;
 
/*******************Timmer setup*************************************/
/********************************************************************/
//Acceleration control
volatile unsigned int AccelerationVal=50;
unsigned long decelerateStepPoint=9000;


#define bbs(x)  (1<<x)
 // Microstep=16; 1.8deg per step, one revolution = 3200steps 
 // one revolution = 8mm. 3200 steps=8mm. 
 // one timer tick = 1/2 period => 800 ticks per mm

// Prescaler = 64
//16Mhz/64=0.25Mhz 1/0.25=4us 4*10=40us => 
const uint8_t myTOP = 20;//max speed=15,
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


/************Wrist2 STEPPER SETUP****************/
/***************************************************/

// To indicate if stepper is working. 
// If yes, True ; otherwise, False

volatile  unsigned long StepCounter_Wrist2=0;
volatile bool DirectionFlag_Wrist2=0;
volatile  unsigned long Wrist2Stepper_TotalSteps=0;
volatile bool Wrist2Stepper_WorkingFlag=false;
volatile  static bool sentFlag_Wrist2=false; //checking sent signal


const int CP_Wrist2  =  5;      
const int DIR_Wrist2 =  4;      
const int Task_ENA_Wrist2 =  13;
const int Task_ENA_Wrist2_2 =  6;
const int AutoCaliButtonPin = 3;     // the number of the pushbutton pin

// setting Wrist2 stepper driver
void setup_Wrist2Stepper(){
  pinMode(Task_ENA_Wrist2, OUTPUT);
  pinMode(Task_ENA_Wrist2_2, OUTPUT);
  pinMode(DIR_Wrist2, OUTPUT);  
  pinMode(CP_Wrist2,OUTPUT);
  pinMode(AutoCaliButtonPin, INPUT);  
   
  digitalWrite(Task_ENA_Wrist2, HIGH);
  digitalWrite(Task_ENA_Wrist2_2, HIGH);  
  }
  
  
void UpperArmGivenSteps( unsigned long steps,bool Step_direction){  
  
  digitalWrite(Task_ENA_Wrist2, LOW); //Enable sign
  digitalWrite(Task_ENA_Wrist2_2, LOW); //
  Wrist2Stepper_WorkingFlag=true;
  DirectionFlag_Wrist2=Step_direction; 
  Wrist2Stepper_TotalSteps=steps+Wrist2Stepper_TotalSteps;      
  }
  
  void AutoCalibration(){
    //Telling main controller finished to caliration
    
    // if finished to 
    if(digitalRead(AutoCaliButtonPin)==HIGH)
  {
 
    
    sentFlag_Wrist2=true;    
   //Reset parameters
    StepCounter_Wrist2=0;    
    Wrist2Stepper_TotalSteps=0;
    Wrist2Stepper_WorkingFlag=false;
  }
  
  
  }
    
  void UpperArmStepper_ISR(){
  static boolean outputPulse=HIGH;  
  digitalWrite(DIR_Wrist2, DirectionFlag_Wrist2);  //Determin direction
  
  //AutoCalibration();
  
  //determing the task is finished,yes,reset variables
  if((StepCounter_Wrist2==Wrist2Stepper_TotalSteps)||(Wrist2Stepper_WorkingFlag==false)){        
   if((StepCounter_Wrist2==Wrist2Stepper_TotalSteps)&&(Wrist2Stepper_TotalSteps!=0)){
   sentFlag_Wrist2=true;
   }
      
    //Reset parameters
    StepCounter_Wrist2=0;    
    Wrist2Stepper_TotalSteps=0;
    Wrist2Stepper_WorkingFlag=false;
   
    return; // task finished
    }
  
  // if not finished task, flip output
  Wrist2Stepper_WorkingFlag=true; // to indicate the stepper is still working   
  StepCounter_Wrist2++; 
  digitalWrite(CP_Wrist2,outputPulse);
  outputPulse=!outputPulse;
  }  

///// Interrupt Service Routine for TIMER2
ISR(TIMER2_COMPA_vect)
{
  Acceleration_UpperArmStepper_ISR();
}

//Converting string to long
long convStrToLong(){
      long   output_val;
  //converting to long
      unsigned int maxIndex=strValueIndex-1;
      for(int i=0;i<=maxIndex;i++){
      
        lon_ReceivedMotorData=pow(10,maxIndex-i )*double(strValue[i]-'0')+lon_ReceivedMotorData;
      }
      lon_ReceivedMotorData=signedReceivedVale*lon_ReceivedMotorData;         
      output_val=lon_ReceivedMotorData;            
        
      ClearSerialBuffer();  
            
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
      else if(ch == 'f' ) {
        ControlSteppersBySerial();
      }
      else {
        //clear buffer,reset
        ClearSerialBuffer();
        
      }  
                       
      
   }
}

void ClearSerialBuffer(){
  signedReceivedVale=1;
      lon_ReceivedMotorData=0;   
      strValueIndex=0;
      for (int i=0;i<MaxChars;i++){
        strValue[i]=' ';
        }
}

///////////////////////////Accelerating Control
/////////////////////////////////////////////////////////////////////////////////////


void Acceleration_Alg(unsigned long TargetSteps,unsigned long CurrentSteps, long CurrentTargetStepDiff){
      //Check if need to reset speed
      OCR2A = myTOP;    
      
      if((CurrentSteps<=decelerateStepPoint)&&(CurrentSteps<=TargetSteps/2)){      
        OCR2A =  myTOP+(decelerateStepPoint-CurrentSteps)/AccelerationVal;         
      }
      
      if((CurrentTargetStepDiff<=decelerateStepPoint)&&(CurrentSteps>TargetSteps/2)){        
       OCR2A = myTOP+((decelerateStepPoint-(TargetSteps-CurrentSteps))/AccelerationVal);                            
     }                 
}

  
void Acceleration_UpperArmStepper_ISR(){
  unsigned long CurrentTargetStepsDiffer=Wrist2Stepper_TotalSteps-StepCounter_Wrist2;
  Acceleration_Alg(Wrist2Stepper_TotalSteps,StepCounter_Wrist2,CurrentTargetStepsDiffer);  
  UpperArmStepper_ISR();    
}

void setup()
{
  Serial.begin(9600);  
  setMyTimer2( );

  //Setup UpperArmStepper
  setup_Wrist2Stepper();  
}


void loop()
{   
    /*
  if(digitalRead(AutoCaliButtonPin)==LOW)
  {
  Serial.print("low");
  }
  else{
    Serial.println("high");
  }
  
  delay(100);
  */
  SerialCommunication();  
  StepperWorkingCheck(); 
  
}
 
/*************for stepper****************/

//if finished working,send serial a flag
void StepperWorkingCheck(){

   if(sentFlag_Wrist2==true){
     sentFlag_Wrist2=false;     
     digitalWrite(Task_ENA_Wrist2, HIGH);
     digitalWrite(Task_ENA_Wrist2_2, HIGH);
   } 
   
  }


// serial control steppers
void ControlSteppersBySerial(){  
      bool s_direction=0;
      // use atoi to convert the string to an int 
       
      long numSteps = convStrToLong();                                   
      
      if(numSteps>0){
        s_direction=1;
      }else{
        s_direction=0;      
      } 
      numSteps=abs(numSteps);                
      UpperArmGivenSteps(numSteps,s_direction);     

}
