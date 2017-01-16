
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX


const int MotorControENAPin = 7;     // the number of the pushbutton pin

/************PRESURE SENSOR CONTROL STEPPER SETUP********/
/********************************************************/
const int TimmerCounterPeriod=20;

const int analogInPin_Base_DIR0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin_Base_DIR1 = A1;  // Analog input pin that the potentiometer is attached to

  

void MoveStepperByPressureSensor(){
static unsigned long stepCont=0;  
  
int sensorValue_Base_DIR0 = 0;        // value read from the pot
int sensorValue_Base_DIR1 = 0;        // value read from the pot

int outputValue_BaseSensor_DIR0 = 0; 
int outputValue_BaseSensor_DIR1 = 0; 

  sensorValue_Base_DIR0 = analogRead(analogInPin_Base_DIR0);     
  sensorValue_Base_DIR1 = analogRead(analogInPin_Base_DIR1);     
  
  // map it to the range of the analog out:
  outputValue_BaseSensor_DIR0 = map(sensorValue_Base_DIR0, 0, 600, 0, 99);  
  outputValue_BaseSensor_DIR1 = map(sensorValue_Base_DIR1, 0, 750, 0, 99);


 if( digitalRead(MotorControENAPin)==0){
   return;
 }
  
  
  //Motor On/Off Control
  if(outputValue_BaseSensor_DIR0>5){
    
          
          stepCont++;
          //Serial.println(stepCont);
          
          outputValue_BaseSensor_DIR0=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR0)*2;
          String PeriodVal=String(outputValue_BaseSensor_DIR0 );
          PeriodVal+='e';  
          
          mySerial.print(PeriodVal); 
          
          //Serial.println(PeriodVal);         
  
  }   

  if(outputValue_BaseSensor_DIR1>5){
          stepCont++;
         // Serial.println(stepCont);
    
          outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
          outputValue_BaseSensor_DIR1=outputValue_BaseSensor_DIR1*-1;
          String PeriodVal=String(outputValue_BaseSensor_DIR1 );
          PeriodVal+='e';            
          mySerial.print(PeriodVal);    
          //Serial.println(PeriodVal);         
  }

Serial.println(digitalRead(MotorControENAPin));

//delay(10);
}




void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(2000);
  
pinMode(MotorControENAPin, INPUT);

}


void loop() // run over and over
{    
    //MoveStepperByPressureSensor();
    Serial.println("20a;30b;40c;50d;60e;70f;");
    delay(500);
    
}
