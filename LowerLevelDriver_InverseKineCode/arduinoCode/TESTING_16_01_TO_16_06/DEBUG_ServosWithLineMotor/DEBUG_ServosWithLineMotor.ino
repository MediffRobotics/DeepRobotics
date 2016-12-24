#include <math.h>
////////////////////////////////////TIMMER SETUP
#define STEP_LONGER 0
#define STEP_SHORTER 1
#define bbs(x)  (1<<x)
 // Microstep=16; 1.8deg per step, one revolution = 3200steps 
 // one revolution = 8mm. 3200 steps=8mm. 
 // one timer tick = 1/2 period => 800 ticks per mm
#define length_steps_parm 800

// Prescaler = 64
//16Mhz/64=0.25Mhz 1/0.25=4us 4*10=40us => 
const uint8_t myTOP = 39;

volatile int StepperSpeed = 0; //40 us * StepperSpeed =speed us 
volatile int Timer2_Clock_tick = 0;

// stepperSwitch=1: stepper is moving
//              =0: stops by main routine
//             
volatile boolean stepperSwitch=false;
volatile int StepCounter=0;
volatile bool DirectionFlag=0;
volatile int Stepper_TargetSteps=0;

// Assume the shifter is in 0 mm
int stepperPosition=0; 

/////////////////////////////////ROTATE STEPPER SETUP
// the setup function runs once when you press reset or power the board
const int CP_AIXS =  11;     
const int DIR_AIXS =  7;      
const int ENA_AIXS =  4;      
volatile unsigned int StepCounter_AXIS=0;
volatile bool DirectionFlag_AXIS=0;

/*
 * for 51:1 stepper, 1.8deg/step, microstep 16
 1 deg end point: => stepper 51 deg
51/1.8=28.3333333
28.3*16=453.33333 pulses

453.33333*2=906.66666666 clock tick 
*/
const float Angle_to_steps_ArmAxis=453;//
long AxisRotate_TotalSteps=0;

// To indicate if stepper is working. 
// If yes, True ; otherwise, False
//
volatile bool AxisMotor_WorkingFlag=false;

//////////////////////////////////LINEAR STEPPER SETUP
const int CP =  12;      
const int DIR =  8;      
const int ENA =  2;      

///////////////////////////////////Linear motor setup
//SERVO LINEAR MOTOR
int MotorIn1 = 9;     
int MotorIn2 = 10;   
float MotorPosition=-1;
float CurrentAngle_deg=-1;

int PWM_Val_1 = 0;   
int PWM_Val_2 = 0;  

int Global_GivenLinearServoDeg=100;
////////////////////////rotate stepper routine
void setup_rotateStepper(){
  pinMode(ENA_AIXS, OUTPUT);
  pinMode(DIR_AIXS, OUTPUT);  
  pinMode(CP_AIXS,OUTPUT);

  digitalWrite(ENA_AIXS, HIGH);

}

// setting elbow stepper driver
void setElbowStepper(){
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);  
  pinMode(CP,OUTPUT);
  
  }





////////////Rotate back and force
void test_RotateStepper_ControlFromISR(){
  static boolean output_AXIS=HIGH;
  //Direction
  if(StepCounter_AXIS%50000==0){    
    DirectionFlag_AXIS=!DirectionFlag_AXIS;
    digitalWrite(DIR_AIXS, DirectionFlag_AXIS);
    }    
  StepCounter_AXIS++;  
  
  digitalWrite(CP_AIXS,output_AXIS);
  output_AXIS=!output_AXIS;
  }
  
  
  
  
  
  



//**************************************************
//**************************************************

///// Interrupt Service Routine for TIMER2
ISR(TIMER2_COMPA_vect)
{
 
  
  RotateStepper_ControlFromISR();

  ISR_RotateGivenSteps();

 // Set_LinearMotor_Angle(Global_GivenLinearServoDeg);   
  
  
}

//********************************************************
//*******************************************************
void SimplestDemo(){
  
  

  
    //TESTING STEPPER  
  GivenAngle_ElbowStepper(110);
  while(stepperSwitch==true){

  
 //SerialControllingServos();  
  } //wait untile finishe current task  

  Set_LinearMotor_Angle(80);   
  delay(4000);


 GivenAngle_ElbowStepper(70 ); 
 while(stepperSwitch==true){ 
    
 //SerialControllingServos();
 } //wait untile finishe current task



  
 // Set_LinearMotor_Angle(100);   
 // delay(4000);
}




void setup( ) {    
  Serial.begin(9600);  
  
  setMyTimer2( );
  
  //INIT DRIVER WIRES
  setElbowStepper();
  digitalWrite(ENA, HIGH);
  
  //LINEAR MOTOR SERVO
  SETUP_LinearMotor();       
  //setup rotate stepper
  setup_rotateStepper();
 
 
  //Set_LinearMotor_Angle(100);
  

}

bool SettingArmAngles(float UpperArm, float UpperArmAxis,float Elbow){
  //If task finished, return true. otherwise false
  
  GivenAngle_ElbowStepper(95);  
  Global_GivenLinearServoDeg=100;

  
  while(1){               
     } //wait untile finishe current task

  
  }


void loop() {     
  
  //////TASK 1
  //Linear motor
  Set_LinearMotor_Angle(80);
  // elbow stepper 
  GivenAngle_ElbowStepper(100);  
  //axis stepper
  AxisMotor_WorkingFlag=true;
  UpperArmAxis_RotateGivenAngles(-90);
  
  while(AxisMotor_WorkingFlag==true){     
   }
  
 
  ///////TASK2
  //Linear motor
  Set_LinearMotor_Angle(100);
  //axis stepper   
  AxisMotor_WorkingFlag=true;
  UpperArmAxis_RotateGivenAngles(90);
  //elbow
  Serial.print("b");
  ///////
  while(1){
  }
}

/********Axis rotation stepper*****/
/*********************************/
void UpperArmAxis_RotateGivenAngles(float angleVale_deg){
  
    // Determin Direction
  if(angleVale_deg>=0){  
    // Direction 1
    DirectionFlag_AXIS=0;
    
  }else {
    // Direction 2
    DirectionFlag_AXIS=1;
  
  }


  AxisRotate_TotalSteps=Angle_to_steps_ArmAxis*abs(angleVale_deg);
    
  
  delay(1); //have time to go to ISR
  }


////////////Rotate back and force
void RotateStepper_ControlFromISR(){
  static boolean output_AXIS=HIGH;
  

  
  digitalWrite(DIR_AIXS, DirectionFlag_AXIS);  //Determin direction
  
  if(StepCounter_AXIS==AxisRotate_TotalSteps|AxisMotor_WorkingFlag==false){    
    
    //Reset parameters
    
    StepCounter_AXIS=0;
    
    AxisRotate_TotalSteps=0;
    AxisMotor_WorkingFlag=false;
    return; // task finished
    }    
  
  AxisMotor_WorkingFlag=true; // to indicate the stepper is still working    
  StepCounter_AXIS++; 
  digitalWrite(CP_AIXS,output_AXIS);
  output_AXIS=!output_AXIS;
  }



/////////////////////////////////
void GivenAngle_ElbowStepper(float target_deg){

  ////if previous task not finished, skip it.
  if(stepperSwitch){
    return;
    }

    
  float a_sqr_add_b_sqr=57335.876;
  float two_ab=27817.2;  
  //*0.01745329 to convert to rad

  float theta_deg=180-target_deg-11.7;
  float c=sqrt( a_sqr_add_b_sqr-two_ab*cos(theta_deg*0.01745329));

  //Comput how much to move for stepper
  float stepper_MIN_leng=184;
  float StepperMoveTo=c-stepper_MIN_leng;

 
  Stepper_MoveTo(StepperMoveTo);
  //Serial.print("StepperMoveTo: ");
  //Serial.println(StepperMoveTo);
  }

void Stepper_MoveTo(float Moveto_mm){
  // only run it when stepper stops to move
  if((stepperPosition==Moveto_mm)|(stepperSwitch==true)){
    return;
    }
  else if(stepperPosition<Moveto_mm){
    // move longer
    Stepper_ShiftGivenLength(Moveto_mm-stepperPosition,STEP_LONGER);

    stepperPosition=stepperPosition+(Moveto_mm-stepperPosition);
    }  
  else{
    //move shorter
    Stepper_ShiftGivenLength(stepperPosition-Moveto_mm,STEP_SHORTER);
    stepperPosition=stepperPosition-(stepperPosition-Moveto_mm);
    }  
    
  
  }

void Stepper_ShiftGivenLength(float Shift_mm,boolean Direction){
  // Microstep=16; 1.8deg per step, one revolution = 3200steps 
  //one revolution = 8mm. 3200 steps=8mm. 
  // one timer tick = 1/2 period => 800 ticks per mm
  unsigned int TicksNeed=(unsigned int) (length_steps_parm*Shift_mm);
  RotateGivenSteps(TicksNeed,Direction,StepperSpeed); //3200=>one revolution  
  }

void RotateGivenSteps(float TargetSteps,float Direction,int rotate_speed){
      Stepper_TargetSteps=TargetSteps;
      DirectionFlag=Direction;
      StepperSpeed=rotate_speed;
      stepperSwitch=true;  
      }


void ISR_RotateGivenSteps(){
  //Parameter: float StepperSpeed
  //           boolean DirectionFlag
  //           boolean DoneOneRevolution

  //if switch is off, return
  if(stepperSwitch==false) return;
        
   ++Timer2_Clock_tick ;    
   // Elbow stepper
   if((Timer2_Clock_tick>=StepperSpeed)){ 
      Timer2_Clock_tick=0;
      
      static boolean output=HIGH;      
      if(StepCounter==Stepper_TargetSteps){                          
        // If reach the target, reset all
        StepCounter=0;
        Stepper_TargetSteps=0;
        Timer2_Clock_tick=0;
        stepperSwitch=false;
        }
      else{
        digitalWrite(DIR, DirectionFlag);           
        StepCounter++;    
        digitalWrite(CP,output);
        output=!output;
        }
      }
  }


/*********************************************/
/***************LINEAR MOTOR******************/
void Set_LinearMotor_Angle_FromTimmer(){
  float Given_deg=0; 
  Given_deg=Global_GivenLinearServoDeg;
  
  float deg_rad=(3.14159265/180);
  float Angle_Beta=9.09; 
  float Angle_Lamda=18.83;

  float leng_a=253.21;
  float leng_b=60.688;  
  float MotorMinLength=207;

  float theta=180-Given_deg-Angle_Beta-Angle_Lamda;

  float given_rad=theta*deg_rad;
  float convert_cos_ratio=cos(given_rad);
  float Shift_Len=sqrt(leng_a*leng_a+leng_b*leng_b-2*leng_a*leng_b*convert_cos_ratio)-MotorMinLength;
  
  MotorServo_Shifting(Shift_Len);

  //Serial.print("Target leng:");
  //Serial.print(Shift_Len); 
  }


void Set_LinearMotor_Angle(float Given_deg){
  float deg_rad=(3.14159265/180);
  float Angle_Beta=9.09; 
  float Angle_Lamda=18.83;

  float leng_a=253.21;
  float leng_b=60.688;  
  float MotorMinLength=207;

  float theta=180-Given_deg-Angle_Beta-Angle_Lamda;

  float given_rad=theta*deg_rad;
  float convert_cos_ratio=cos(given_rad);
  float Shift_Len=sqrt(leng_a*leng_a+leng_b*leng_b-2*leng_a*leng_b*convert_cos_ratio)-MotorMinLength;
  
  MotorServo_Shifting(Shift_Len);

  //Serial.print("Target leng:");
  //Serial.print(Shift_Len); 
  }

void Get_LinearMotorPosition(){

  //position
  float sensorValue = analogRead(A0);
  float voltage_mv = sensorValue * (5.0 / 1023.0)*1000;
  MotorPosition=57-(57.0/5000.0)*voltage_mv;

 // Serial.print(" MotorPosition:");
  //Serial.print(MotorPosition);   
  }

void SETUP_LinearMotor(){
  pinMode(MotorIn1, OUTPUT);
  pinMode(MotorIn2,OUTPUT); 
 
  }

void Get_MotorServo_Angle(){
  float rad_deg=(180/3.14159265);
  float Angle_Beta=9.09; 
  float Angle_Lamda=18.83;

  float leng_a=253.21;
  float leng_b=60.688;  
  float leng_c=207+MotorPosition;
  //cos(Theta)=(253^2-60^2-c^2)/(2*253*60)
  //=>cos(Theta)=21.969-c^2/30381
  //=>Theta=arccos(21.969-c^2/30381)
      
  float acos_radio=(leng_a*leng_a+leng_b*leng_b-leng_c*leng_c)/(2*leng_a*leng_b);
  float Theta_deg=acos(acos_radio)*rad_deg;
  CurrentAngle_deg=180-Angle_Beta-Angle_Lamda-Theta_deg;

  Serial.print(" Angle: ");
  Serial.println(CurrentAngle_deg);
  
  
  
  
  }  

float MotorServo_Shifting(float Desired_position){
  //Return: Valtage in mV. 
  // Parameter: Desired_position: where you want it be  
  
  // Move to given position
  // potential meter range: 0-57mm
  // voltage range: 0-5000mV => 5000mV/57mm=87.7=88mV/mm
  // safe range: 2mm-57mm => 200mV-5000mV
  if(Desired_position<2) Desired_position=2.0;
  if(Desired_position>57) Desired_position=57.0; 
  
  Desired_position=57-Desired_position;
  float accelerating_Target=0;
  //(5000mV/57mm)*targetPosition
  float target_mV=(5000.0/57.0)*Desired_position;   
  float sensorValue = analogRead(A0);
  float voltage_mv = sensorValue * (5.0 / 1023.0)*1000;
  float error= target_mV-voltage_mv ; 
  float abs_error=abs(error);

  if(abs_error<=4){
     ResetMotorPin();
    return voltage_mv ;
    }
  
  // if error less than 44mV( 0.5mm), done
  else{
    
      if(error>0){

        //if(Timer2_Clock_tick%10000)
        
        if(abs_error<=10){
          MovingShorter(115);  
          }
        else if (abs_error<=100){   
        MovingShorter(120);  }

        else if(abs_error<=200){
          MovingShorter(130);  
          }
        else if(abs_error<=300){
          MovingShorter(150);  
          }
        else if(abs_error<=400){
          MovingShorter(170);  
          }  
          
        else {
          MovingShorter(200);   
          }

            
        }
      else{
        // Optimal speed                       
        
        if(abs_error<=10){
           MovingLonger(45);
           }           
        else if(abs_error<=100){
          MovingLonger(50);
          }

        else if(abs_error<=200){
          MovingLonger(55);
          }  
         else if(abs_error<=300){
          MovingLonger(60);
          }    

         else if(abs_error<=400){
          MovingLonger(65);
          }
         else if(abs_error<=500){
          MovingLonger(70);
          }   
        else{
          MovingLonger(150);
          }      
                       
        }  
    }

  return voltage_mv;
  
  }
  
void MovingShorter(float PWM_speed){
  //SHORTER
  digitalWrite(MotorIn2, LOW);
  //digitalWrite(MotorIn1, HIGH);  
  analogWrite(MotorIn1, PWM_speed);  
  }

void MovingLonger(float PWM_speed){
  //LONGER
 //digitalWrite(MotorIn2, HIGH);
 digitalWrite(MotorIn1,LOW ); 
 analogWrite(MotorIn2, PWM_speed);
  }

void ResetMotorPin(){
  pinMode(MotorIn1, INPUT);
  pinMode(MotorIn2,INPUT);   
  pinMode(MotorIn1, OUTPUT);
  pinMode(MotorIn2,OUTPUT);
  pinMode(MotorIn1, LOW);
  pinMode(MotorIn2,LOW);
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




