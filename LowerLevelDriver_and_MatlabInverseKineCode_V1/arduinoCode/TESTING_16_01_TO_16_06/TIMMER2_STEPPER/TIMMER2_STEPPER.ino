
////////////////////////////////////TIMMER SETUP
#define bbs(x)  (1<<x)
const int Timer2Clock_Stepper1 = 5;   // 5 *0.02ms =0.1ms =>5khz
// Prescaler = 64
const uint8_t myTOP = 4;  // 20us  when Prescaler == 64

//////////////////////////////////MOTOR DRIVER SETUP
const int CP =  11;      
const int DIR =  7;      
const int ENA =  4;      
volatile int StepCounter=0;
volatile bool DirectionFlag=0;

///// Interrupt Service Routine for TIMER2
ISR(TIMER2_COMPA_vect)
{
   //Calling stepper control program
   static unsigned int SetClock_Stepper1 = 0; 
   ++SetClock_Stepper1 ; 
   if(!(SetClock_Stepper1%Timer2Clock_Stepper1)){ 
      Timer2_Stepper1Control( );
   }

}
void setup( ) {
  //INIT DRIVER WIRES
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);  
  pinMode(CP,OUTPUT);

  //INIT TIMER2
  setMyTimer2( );
}

void loop() {
  digitalWrite(ENA, HIGH);
  
}
//  The control program for Steper1(linear steper)
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


////////
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

