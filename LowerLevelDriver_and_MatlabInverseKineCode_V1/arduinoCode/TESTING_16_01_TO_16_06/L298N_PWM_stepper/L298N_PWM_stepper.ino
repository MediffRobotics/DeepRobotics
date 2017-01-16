int Pin0 = 19;
int Pin1 = 8;
int Pin2 = 12;
int Pin3 = 13;

// pwm related
int ValPWM_P0=0,ValPWM_P1=0, ValPWM_P2=0,ValPWM_P3=0;
bool PreP0=0,PreP1=0,PreP2=0,PreP3=0; // decrease or increase pwm
const int MaxValPWM=5;

//Control stepper related
int _step =0 ;

void setup() {
  // put your setup code here, to run once:
  pinMode(Pin0, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
}


void loop() {
  
  for (int i=0;i<=500;i++){
    
    up();  
    }
 
    
  for (int i=0;i<=500;i++){
      //down();
  }
 
 
}
  void up()
{ 
  
  switch(_step){
    case 0:
    
      StepperBuffer(1,0,0,0);
   
    break;
    case 1:
      StepperBuffer(1,0,1,0);

    break;
    case 2:
      StepperBuffer(0,0,1,0);
     
    break;
    case 3:
      StepperBuffer(0,1,1,0);     
    break;
    case 4:
      StepperBuffer(0,1,0,0);  
  
    break;
    case 5:
      StepperBuffer(0,1,0,1);
     
    break;
      case 6:
      StepperBuffer(0,0,0,1);
    break;
    case 7:
      StepperBuffer(1,0,0,1);      
    break;
    default:
      StepperBuffer(0,0,0,0);      
    break;
  }
    _step++;
 
  if(_step>7){    _step=0;  }
 

}


void down()
  {
   
    switch(_step){
    case 0:
 
      StepperBuffer(0,0,0,1);
    break;
    case 1:
    StepperBuffer(0,1,0,1);
    break;
    case 2:
    StepperBuffer(0,1,0,0);
    
    break;
    case 3:
    StepperBuffer(0,1,1,0);
 
    break;
    case 4:
    StepperBuffer(0,0,1,0);

    break;
    case 5:
    StepperBuffer(1,0,1,0);
   
    break;
      case 6:
      StepperBuffer(1,0,0,0);
     
    break;
    case 7:
    StepperBuffer(1,0,0,1);

    break;
    default:
      StepperBuffer(0,0,0,0);
 
    break;
  }
   _step++; 
  if(_step>7){_step=0;}  
  } 



void StepperBuffer(bool P0,bool P1,bool P2,bool P3){
  // useing pwm to let digital changes be smother
  
  int sing0=P0-PreP0;
  int sing1=P1-PreP1;
  int sing2=P2-PreP2;
  int sing3=P3-PreP3;
  
  PreP0=P0;//Update previous logic 
  PreP1=P1;
  PreP2=P2;
  PreP3=P3;
  
  for(int i=0;i<=10;i++){

    ValPWM_P0+=sing0;// p0 pwm
    ValPWM_P1+=sing1;// p1 pwm
    ValPWM_P2+=sing2;// p2 pwm
    ValPWM_P3+=sing3;// p0 pwm
    
    //Update PWM
    //0.05ms*400times=20ms per step(1.8deg)
    //20ms*200steps=4000ms per revolution
    MultiplePWM_OR_StepperFrequency(1);     
    }
      
  };


void MultiplePWM_OR_StepperFrequency(int NumPhases){
   

  
    
   for (int j=0;j<=NumPhases;j++){
        OnePhasePWM(); //Decrease or increase pwm by once
        //PWMoverFlowError();// Check pwm value error
        }
  
  }

  
void OnePhasePWM(){
  int j=0,k=0,l=0,m=0;
  
  for(int i=0;i<=MaxValPWM;i++){
     //p0
     if(j<ValPWM_P0){
      digitalWrite(Pin0, HIGH);
      }
     else{
      digitalWrite(Pin0, LOW);          
     } 

      //p1
     if(k<ValPWM_P1){
      digitalWrite(Pin1, HIGH);}
     else{
      digitalWrite(Pin1, LOW);          
     } 
     
      //p2
     if(l<ValPWM_P2){
      digitalWrite(Pin2, HIGH);}
     else{
      digitalWrite(Pin2, LOW);          
     } 


      //p3
     if(m<ValPWM_P3){
      digitalWrite(Pin3, HIGH);}
     else{
      digitalWrite(Pin3, LOW);          
     } 

     

    // delay for a while
    // one phase has 10 parts
    // 1us*50=50us=0.05ms>20khz is pwm frequency
    delayMicroseconds(5); 
   // delay(1000); 
    //Update pwm val 
    j++;
    k++;
    l++;
    m++;
    }
  
  }

void PWMoverFlowError(){
  if(0>ValPWM_P0||ValPWM_P0>MaxValPWM
    ||0>ValPWM_P1||ValPWM_P1>MaxValPWM
    ||0>ValPWM_P2||ValPWM_P2>MaxValPWM
    ||0>ValPWM_P3||ValPWM_P3>MaxValPWM
   ){
    while(1){
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
      delay(500);
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      delay(500);
      
      }
    }
  }  
