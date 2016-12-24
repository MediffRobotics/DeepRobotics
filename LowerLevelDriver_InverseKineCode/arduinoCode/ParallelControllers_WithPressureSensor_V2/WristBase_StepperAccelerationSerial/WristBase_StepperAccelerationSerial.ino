/*
//13166006503 2016/07/11 shanghai baoshan motanjianglu
// menpai:1512  0258liwei 
*/

/********************SERIAL BUFFER**********************************/
/******************************************************************/
//a buffer to save digits
const int MaxChars=8;   // an int string contains up to 8 digits and is terminated 
char strValue[MaxChars]; // must be big enough for digits and terminating null
int strValueIndex=0; // the index into the array storing the received digits
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
void setMyTimer2(unsigned int Period){
  cli();  // 禁止中斷
  TCCR2A = bbs(WGM21);  // CTC mode 2; Clear Timer on Compare, see p.158-162
  TCCR2B = bbs(CS22);  // Prescaler == 64; see p.162 in datasheet 
  ///// 注意 WGM22 在 TCCR2B, 但 WGM21 與 WGM20 在 TCCR2A; 
  ///// mode 由 WGM22, WGM21, WGM20 決定 (see datasheet p.158-162)
  OCR2A = Period;  // TOP count for CTC, 與 prescaler 有關
  TCNT2=0;  // counter 歸零 
  TIMSK2 |= bbs(OCIE2A);  // enable CTC for TIMER2_COMPA_vect
  sei();  // 允許中斷
}

int ReceivedMotorPeriodValue= myTOP;
/************PRESURE SENSOR CONTROL STEPPER SETUP********/
/********************************************************/
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 13; // Analog output pin that the LED is attached to
 int TeachingModeSwitch=0;

int sensorValue = 0;        // value read from the pot
int outputValue = 0;   

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
  
/********************Controlling steppers by sensor****/
/*****************************************************/
  
void UpperArmGivenSteps_Period(long numPeriod){  
      int steps=0;
      bool Step_direction;      
      // use atoi to convert the string to an int                                                               
      if(numPeriod>0){
        Step_direction=1;
      }else{
        Step_direction=0;      
      } 
 
      
      if(abs(numPeriod)>=50){
        steps=10;      
      }
      else{
        steps=500;      
      } 
  //steps=500;
  Wrist2Stepper_WorkingFlag=true;
  DirectionFlag_Wrist2=Step_direction; 
  Wrist2Stepper_TotalSteps=steps+Wrist2Stepper_TotalSteps;      
  }
  
 void PressureSensorControl_Wrist2Stepper_ISR(){
  static boolean outputPulse=HIGH;  
  digitalWrite(DIR_Wrist2, DirectionFlag_Wrist2);  //Determin direction

  //determing the task is finished,yes,reset variables
  if((StepCounter_Wrist2==Wrist2Stepper_TotalSteps)||(Wrist2Stepper_WorkingFlag==false)){
    
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


 
/*************for stepper****************/
void CheckToEnablePinToReceivingNewData(){

  if(Wrist2Stepper_WorkingFlag==true){
      digitalWrite(Task_ENA_Wrist2, LOW);
      digitalWrite(Task_ENA_Wrist2_2, LOW);
  }else{
     digitalWrite(Task_ENA_Wrist2, HIGH);
     digitalWrite(Task_ENA_Wrist2_2, HIGH);
  }
  
}

const int PeriodBufferLength=2;
long PeriodBuffer[PeriodBufferLength]={0,0};//a stack
int PeriodBufferWriteIndex=0;
int PeriodBufferReadIndex=0;
void MotorMoveBuffer_Recording(){
  
  long numPeriod = convStrToLong();
  
  if(numPeriod==0){
    return;
  }
  
  if(PeriodBuffer[PeriodBufferWriteIndex]==0){
    
    PeriodBuffer[PeriodBufferWriteIndex]=numPeriod;
      PeriodBufferWriteIndex++;
      if(PeriodBufferWriteIndex==PeriodBufferLength){
        PeriodBufferWriteIndex=0;
      }
      
  }

}

long MotorMoveBuffer_Reading(){
  
  if(PeriodBuffer[PeriodBufferReadIndex]!=0){    
      long returnData=PeriodBuffer[PeriodBufferReadIndex];
      PeriodBuffer[PeriodBufferReadIndex]=0;
      PeriodBufferReadIndex++;
       if(PeriodBufferReadIndex==PeriodBufferLength){
          PeriodBufferReadIndex=0;
          } 
      return returnData;
  }  
  return 0;
    
}

  
// serial control steppers
void ControlSteppersBySerialQueue(){  
  
      //check if rady to update a new move.
      //if not, return. else retrieve from data buffer     
      //if stepper still moving, dont update Wrist2Stepper_WorkingFlag
      if(Wrist2Stepper_WorkingFlag==1) return;
       
        long numPeriod=MotorMoveBuffer_Reading();         
        if(numPeriod==0){ // for invalid number
          return;
        }   
   
      //Serial.print("Readed data: ");
      //Serial.println(numPeriod);   
      ChangingPeriodByData(abs(numPeriod));  //Changing period first      
      UpperArmGivenSteps_Period(numPeriod);          
}


bool CheckingIfDataBufferFull(){
  //if buffer not full,return false. 
  for(int i=0;i<PeriodBufferLength;i++){
    if(PeriodBuffer[i]==0){
      return false;
    }
  }
  return true;
}


void ChangingPeriodByData(unsigned int periodVal){  
  static unsigned long stepcount=0;    
  stepcount++;
  setMyTimer2(periodVal); 

}
/*********************ISR****************************/
/**************************************************/
     
///// Interrupt Service Routine for TIMER2
ISR(TIMER2_COMPA_vect)
{
  PressureSensorControl_Wrist2Stepper_ISR();
  
  Acceleration_UpperArmStepper_ISR();
}


/******************RECEIVING DATA***************/
/************************************************/
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
      else if(ch == 'd' ) {
        //Control stepper by period data
        MotorMoveBuffer_Recording();        
      }
      
        //Control stepper by steps data
       else if(ch == 'D' ) {
         
         ControlSteppersBySerial();
         //todo
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

  
/************************************************/
/************************************************/

void setup()
{
  Serial.begin(115200);    
  setMyTimer2(myTOP );
  //Setup UpperArmStepper
  setup_Wrist2Stepper();  
}


void loop()
{   

  SerialCommunication();    
  //Work stepper  
  ControlSteppersBySerialQueue(); 
  // Check if can set enable pin
  CheckToEnablePinToReceivingNewData();
 
}
 
/***************Control stepper by numSteps data*************************/
/************************************************************************/

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

void UpperArmGivenSteps( unsigned long steps,bool Step_direction){  
  
  digitalWrite(Task_ENA_Wrist2, LOW); //Enable sign
  digitalWrite(Task_ENA_Wrist2_2, LOW); //
  Wrist2Stepper_WorkingFlag=true;
  DirectionFlag_Wrist2=Step_direction; 
  Wrist2Stepper_TotalSteps=steps+Wrist2Stepper_TotalSteps;      
  }
