#include <math.h>
#include <Servo.h>
////////////////////////////////////TIMMER SETUP
#define STEP_LONGER 0
#define STEP_SHORTER 1
#define bbs(x)  (1<<x)
 // Microstep=16; 1.8deg per step, one revolution = 3200steps 
  //one revolution = 8mm. 3200 steps=8mm. 
  // one timer tick = 1/2 period => 800 ticks per mm
#define length_steps_parm 800

// Prescaler = 64
//16Mhz/64=0.25Mhz 1/0.25=4us 4*10=40us => 

const uint8_t myTOP = 39;

//40 us * 5 =200 us 

volatile int StepperSpeed = 0; 
volatile int Timer2_Clock_tick = 0;
// stepperSwitch=1: stepper will move
//              =0: stops
volatile boolean stepperSwitch=false;
//volatile RotateGivenSteps=-1;
volatile int StepCounter=0;
volatile bool DirectionFlag=-1;
volatile int Stepper_TargetSteps=0;

// Assume the shifter is in 0 mm
int stepperPosition=0; 

/////////////////////////////////ROTATE STEPPER SETUP
// the setup function runs once when you press reset or power the board
const int CP_AIXS =  11;     
const int DIR_AIXS =  7;      
const int ENA_AIXS =  4;      
volatile int StepCounter_AXIS=0;
volatile bool DirectionFlag_AXIS=0;


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

//****************************************************

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
         
         // Serial.println(MyServoGlobal.strValue);     
                         
          // use atoi to convert the string to an int 
          MyServoGlobal.pos = atoi(MyServoGlobal.strValue);   
                                
          MyServoGlobal.myservo[ch - 'a'].write(MyServoGlobal.pos); 
          MyServoGlobal.index=0;     
         // Serial.print(MyServoGlobal.strValue);
         // Serial.println(ch); 
          
      }
    }
}


/////////////////////////////////////////////////////////
////////////////////////rotate stepper routine
void setup_rotateStepper(){
  pinMode(ENA_AIXS, OUTPUT);
  pinMode(DIR_AIXS, OUTPUT);  
  pinMode(CP_AIXS,OUTPUT);

}

///////////RotateDirection1
/*

void RotateDirection1(int numSteps)
{
    if(StepCounter_AXIS%5000==0){    
       DirectionFlag_AXIS=!DirectionFlag_AXIS;
      digitalWrite(DIR_AIXS, DirectionFlag_AXIS);
    }    
  StepCounter_AXIS++;  
  

}
*/

////////////Rotate back and force
void RotateStepper_ControlFromISR(){
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
//  SerialControllingServos();   
   //Calling stepper control program
 
  RotateStepper_ControlFromISR();

  ISR_RotateGivenSteps();
  
  
}

//********************************************************
//*******************************************************
void SimplestDemo(){
  
  

  
    //TESTING STEPPER  
  GivenAngle_Stepper(110);
  while(stepperSwitch==true){

  
 //SerialControllingServos();  
  } //wait untile finishe current task  

  Set_LinearMotor_Angle(80);   
  delay(4000);


 GivenAngle_Stepper(70 ); 
 while(stepperSwitch==true){ 
    
 //SerialControllingServos();
 } //wait untile finishe current task



  
  Set_LinearMotor_Angle(100);   
  delay(4000);
}



void setup( ) {    
  delay  (3000);  
  Serial.begin(9600);
  //|Init servos
  //InitServos(); 

  //INIT TIMER2
  setMyTimer2( );
  
  //INIT DRIVER WIRES
  setElbowStepper();
  digitalWrite(ENA, HIGH);
  
  //LINEAR MOTOR SERVO
  SETUP_LinearMotor();    
  

  
  //setup rotate stepper
  setup_rotateStepper();
  digitalWrite(ENA_AIXS, HIGH);
 
 Set_LinearMotor_Angle(100);
 delay(5000);
  
}

void loop() {

  SimplestDemo();
  //shoulder Linear motor       
 // Get_LinearMotorPosition();  
 // Get_MotorServo_Angle();        
  //Set_LinearMotor_Angle(90); 
    
    
  //SerialControllingServos();  
  /*  
    
  //TESTING STEPPER  
  GivenAngle_Stepper(80);
  while(stepperSwitch==true){    
 //SerialControllingServos();  
  } //wait untile finishe current task  


 GivenAngle_Stepper(90); 
 while(stepperSwitch==true){ 
 //SerialControllingServos();
 } //wait untile finishe current task
  
    */
  
}

void GivenAngle_Stepper(float target_deg){
  
  float a_sqr_add_b_sqr=57335.876;
  float two_ab=27817.2;  
  //*0.01745329 to convert to rad

  float theta_deg=180-target_deg-11.7;
  float c=sqrt( a_sqr_add_b_sqr-two_ab*cos(theta_deg*0.01745329));

  //Comput how much to move for stepper
  float stepper_MIN_leng=184;
  float StepperMoveTo=c-stepper_MIN_leng;

 
  Stepper_MoveTo(StepperMoveTo);
   Serial.print("StepperMoveTo: ");
  Serial.println(StepperMoveTo);
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
  RotateGivenSteps(TicksNeed,Direction,2); //3200=>one revolution
  
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





// setting elbow stepper driver
void setElbowStepper(){
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);  
  pinMode(CP,OUTPUT);
  
  }


  ///////////////////////////////////////////////////////
//The control program for Steper1(linear steper)
void Timer2_Stepper1Control( ) {
   static boolean output=HIGH;
  //Reverse Direction every 500 steps
  if(StepCounter%10000==0){    
    DirectionFlag=!DirectionFlag;
    digitalWrite(DIR, DirectionFlag);
    }    
  StepCounter++;  
  
  digitalWrite(CP,output);
  output=!output;
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

  Serial.print(" MotorPosition:");
  Serial.print(MotorPosition);   
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




