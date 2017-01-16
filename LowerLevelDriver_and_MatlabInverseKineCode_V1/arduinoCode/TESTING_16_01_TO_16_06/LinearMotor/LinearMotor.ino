/*
 Fade

 This example shows how to fade an MotorIn1 on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */

int MotorIn1 = 9;     
int MotorIn2 = 10;     

int PWM_Val_1 = 0;   
int PWM_Val_2 = 0;  
int fadeAmount_1 = 5; // how many points to fade the MotorIn1 by
int fadeAmount_2 = 5; // how many points to fade the MotorIn1 by

// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(MotorIn1, OUTPUT);
  pinMode(MotorIn2,OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
PWM_CONTROL_MOTOR();

}
float MotorServo(float Target_valtage_mV){
  //Return: Valtage in mV 
   return 0;
  
  }


void PWM_CONTROL_MOTOR(){
  PWM_Val_1=0;
  PWM_Val_2=0;
  
  
  for(int i=1;i<=50;i++){
    MovingShorter();
    }
   ResetMotorPin(); 
   delay(1000);
    
/*
  for(int i=1;i<=50;i++){  
    MovingLonger();
    }*/
    ResetMotorPin();
    delay(1000);
  }

void ResetMotorPin(){
  pinMode(MotorIn1, INPUT);
  pinMode(MotorIn2,INPUT);   
  pinMode(MotorIn1, OUTPUT);
  pinMode(MotorIn2,OUTPUT);
  pinMode(MotorIn1, LOW);
  pinMode(MotorIn2,LOW);
  }

void MovingShorter(){
  //       SHORTER
  digitalWrite(MotorIn2, LOW);
  
  analogWrite(MotorIn1, PWM_Val_1);  
  // change the PWM_Val_1 for next time through the loop:
  PWM_Val_1 = PWM_Val_1 + fadeAmount_1;
  // reverse the direction of the fading at the ends of the fade:
  if (PWM_Val_1 == 0 || PWM_Val_1 == 255) {
    fadeAmount_1 = -fadeAmount_1 ;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(300);
  
  }

void MovingLonger(){
  // set the PWM_Val_1 of pin 9:

  
 //        LONGER
 //digitalWrite(MotorIn2, HIGH);
 digitalWrite(MotorIn1,LOW ); 
  
  
  analogWrite(MotorIn2, PWM_Val_2);
  

  // change the PWM_Val_1 for next time through the loop:
  PWM_Val_2 = PWM_Val_2 + fadeAmount_2;

  // reverse the direction of the fading at the ends of the fade:
  if (PWM_Val_2 == 0 || PWM_Val_2 == 255) {
    fadeAmount_2 = -fadeAmount_2 ;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(100);
    
  }
