
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

const float Alpha=0.1;

const int Base_MotorControENAPin = 8;     // the number of the pushbutton pin
const int UpArm_MotorControENAPin = 9;     // the number of the pushbutton pin
const int Elbow_MotorControENAPin = 10;     // the number of the pushbutton pin
const int WristBase_MotorControENAPin = 11;     // 
const int Wrist1_MotorControENAPin = 12;     // 
const int Wrist2_MotorControENAPin = 13;     // 

/************PRESURE SENSOR CONTROL STEPPER SETUP********/
/********************************************************/
const int TimmerCounterPeriod=20;




/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////



void DecideSending_Base_DataByENA(){
   if( digitalRead(Base_MotorControENAPin)==0){ //  
       return;               
   }
   SendData_BaseMotorByPressSensor();    
   
   
   if(SendData_BaseMotorByPressSensor()==true){         
     while(digitalRead(Base_MotorControENAPin)==1){}
   }
   //Checking if nanos  received 
   //delay(10);       
   //while(digitalRead(Base_MotorControENAPin)==1){}
   
   
}

bool SendData_BaseMotorByPressSensor(){
  static float Qk1=460;
  static float Qk=0;
  
  static float Pk1=460;
  static float Pk=0;
  
  const int analogInPin_Base_DIR0 = A0;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Base_DIR1 = A1;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Base_DIR0 = 0;        // value read from the pot
  int sensorValue_Base_DIR1 = 0;        // value read from the pot
  
  int outputValue_BaseSensor_DIR0 = 0; 
  int outputValue_BaseSensor_DIR1 = 0; 
   
    //send one new move
  //Direction0
  Qk= analogRead(analogInPin_Base_DIR0);
  Qk1=Qk1+Alpha*(Qk-Qk1);
  sensorValue_Base_DIR0 =int(Qk1);
  
  //Direction1    
  Pk = analogRead(analogInPin_Base_DIR1); 
  Pk1=Pk1+Alpha*(Pk-Pk1);
  sensorValue_Base_DIR1=Pk1;
    
  // map it to the range of the analog out:
  outputValue_BaseSensor_DIR0 = map(sensorValue_Base_DIR0, 0, 380, 0, 99);  
  outputValue_BaseSensor_DIR1 = map(sensorValue_Base_DIR1, 0, 380, 0, 99);
   //Serial.println(Qk);
    //Motor On/Off Control
    if( Qk<360){       
            //outputValue_BaseSensor_DIR0=TimmerCounterPeriod+outputValue_BaseSensor_DIR0;
            String PeriodVal=String(int(outputValue_BaseSensor_DIR0));
            PeriodVal+="a;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);       
           return true;         
    }   
  
    if(Pk<360){
            //outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
            outputValue_BaseSensor_DIR1=outputValue_BaseSensor_DIR1*-1;
            String PeriodVal=String(outputValue_BaseSensor_DIR1);
            PeriodVal+="a;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
    
          return true;        
    }
    
    return false;
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void DecideSending_UpArm_DataByENA(){
  
   if( digitalRead(UpArm_MotorControENAPin)==0){ //  
   
       //Serial.println("Up arm returned");
       //delay(100);
       return;               
   }
   
   if(SendData_UpArm_MotorByPressSensor()==true){         
     while(digitalRead(UpArm_MotorControENAPin)==1){}
   }
   
   //SendData_UpArm_MotorByPressSensor();    
   //delay(10);       
}

bool SendData_UpArm_MotorByPressSensor(){
  static float Qk1=460;
  static float Qk=0;
  
  static float Pk1=460;
  static float Pk=0;
  
  const int analogInPin_Base_DIR0 = A2;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Base_DIR1 = A3;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Base_DIR0 = 0;        // value read from the pot
  int sensorValue_Base_DIR1 = 0;        // value read from the pot
  
  int outputValue_BaseSensor_DIR0 = 0; 
  int outputValue_BaseSensor_DIR1 = 0; 
   
    //send one new move
  //Direction0
  Qk= analogRead(analogInPin_Base_DIR0);
  Qk1=Qk1+Alpha*(Qk-Qk1);
  sensorValue_Base_DIR0 =int(Qk1);
  
  //Direction1    
  Pk = analogRead(analogInPin_Base_DIR1); 
  Pk1=Pk1+Alpha*(Pk-Pk1);
  sensorValue_Base_DIR1=Pk1;
    
  //Serial.println(Qk);
  
  // map it to the range of the analog out:
  outputValue_BaseSensor_DIR0 = map(sensorValue_Base_DIR0, 0, 380, 0, 99);  
  outputValue_BaseSensor_DIR1 = map(sensorValue_Base_DIR1, 0, 380, 0, 99);
   //Serial.println(Qk);
    //Motor On/Off Control
    if( Qk<360){       
            //outputValue_BaseSensor_DIR0=TimmerCounterPeriod+outputValue_BaseSensor_DIR0;
            String PeriodVal=String(int(outputValue_BaseSensor_DIR0));
            PeriodVal+="b;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);       
           return true;         
    }   
  
    if(Pk<360){
            //outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
            outputValue_BaseSensor_DIR1=outputValue_BaseSensor_DIR1*-1;
            String PeriodVal=String(outputValue_BaseSensor_DIR1);
            PeriodVal+="b;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
    
          return true;        
    }
    
    //Serial.println("vAL QK: ");
    //Serial.println(Qk);
    return false;
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void DecideSending_Elbow_DataByENA(){
  
   if( digitalRead(Elbow_MotorControENAPin)==0){ //  
       return;               
   }
   
   
    if(SendData_Elbow_MotorByPressSensor()==true){         
     while(digitalRead(Elbow_MotorControENAPin)==1){}
   }
   //SendData_Elbow_MotorByPressSensor();    
   //delay(10);       
}

bool SendData_Elbow_MotorByPressSensor(){
  static float Qk1=460;
  static float Qk=0;
  
  static float Pk1=460;
  static float Pk=0;
  
  const int analogInPin_Base_DIR0 = A4;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Base_DIR1 = A5;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Base_DIR0 = 0;        // value read from the pot
  int sensorValue_Base_DIR1 = 0;        // value read from the pot
  
  int outputValue_BaseSensor_DIR0 = 0; 
  int outputValue_BaseSensor_DIR1 = 0; 
   
    //send one new move
  //Direction0
  Qk= analogRead(analogInPin_Base_DIR0);
  Qk1=Qk1+Alpha*(Qk-Qk1);
  sensorValue_Base_DIR0 =int(Qk1);
  
  //Direction1    
  Pk = analogRead(analogInPin_Base_DIR1); 
  Pk1=Pk1+Alpha*(Pk-Pk1);
  sensorValue_Base_DIR1=Pk1;
    
  //Serial.println(Qk);
  
  // map it to the range of the analog out:
  outputValue_BaseSensor_DIR0 = map(sensorValue_Base_DIR0, 0, 380, 0, 99);  
  outputValue_BaseSensor_DIR1 = map(sensorValue_Base_DIR1, 0, 380, 0, 99);
   //Serial.println(Qk);
    //Motor On/Off Control
    if( Qk<360){       
            //outputValue_BaseSensor_DIR0=TimmerCounterPeriod+outputValue_BaseSensor_DIR0;
            String PeriodVal=String(int(outputValue_BaseSensor_DIR0));
            PeriodVal+="c;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);       
           return true;         
    }   
  
    if(Pk<360){
            //outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
            outputValue_BaseSensor_DIR1=outputValue_BaseSensor_DIR1*-1;
            String PeriodVal=String(outputValue_BaseSensor_DIR1);
            PeriodVal+="c;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
    
          return true;        
    }
    
    return false;
}

/*****************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void DecideSending_WristBase_DataByENA(){
  
   if( digitalRead(WristBase_MotorControENAPin)==0){ //  WristBase_MotorControENAPin
       return;               
   }
   
   if(SendData_WristBase_MotorByPressSensor()==true){         
     while(digitalRead(WristBase_MotorControENAPin)==1){}
   }
   //SendData_WristBase_MotorByPressSensor();    
   //delay(500);       
}

bool SendData_WristBase_MotorByPressSensor(){
  static float Qk1=460;
  static float Qk=0;
  
  static float Pk1=460;
  static float Pk=0;
  
  const int analogInPin_Base_DIR0 = A6;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Base_DIR1 = A7;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Base_DIR0 = 0;        // value read from the pot
  int sensorValue_Base_DIR1 = 0;        // value read from the pot
  
  int outputValue_BaseSensor_DIR0 = 0; 
  int outputValue_BaseSensor_DIR1 = 0; 
   
    //send one new move
  //Direction0
  Qk= analogRead(analogInPin_Base_DIR0);
  Qk1=Qk1+Alpha*(Qk-Qk1);
  sensorValue_Base_DIR0 =int(Qk1);
  //Serial.print("Qk1:");
  //Serial.println(Qk1); 
  //Direction1    
  Pk = analogRead(analogInPin_Base_DIR1); 
  Pk1=Pk1+Alpha*(Pk-Pk1);
  sensorValue_Base_DIR1=Pk1;
    
  //Serial.println(Qk);
  
  // map it to the range of the analog out:
  outputValue_BaseSensor_DIR0 = map(sensorValue_Base_DIR0, 0, 380, 0, 99);  
  outputValue_BaseSensor_DIR1 = map(sensorValue_Base_DIR1, 0, 380, 0, 99);
   //Serial.println(Qk);
    //Motor On/Off Control
    if( Qk<360){       
            //outputValue_BaseSensor_DIR0=TimmerCounterPeriod+outputValue_BaseSensor_DIR0;
            String PeriodVal=String(int(outputValue_BaseSensor_DIR0));
            PeriodVal+="d;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);       
           return true;         
    }   
  
    if(Pk<360){
            //outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
            outputValue_BaseSensor_DIR1=outputValue_BaseSensor_DIR1*-1;
            String PeriodVal=String(outputValue_BaseSensor_DIR1);
            PeriodVal+="d;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
    
          return true;        
    }
    
    return false;
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void DecideSending_Wrist1_DataByENA(){
  
   if( digitalRead(Wrist1_MotorControENAPin)==0){ //  
       return;               
   }
   
   
   //Detecting receiving
   if(SendData_Wrist1_MotorByPressSensor()==true){         
     while(digitalRead(Wrist1_MotorControENAPin)==1){}
   }
   //SendData_Wrist1_MotorByPressSensor();    
   //delay(500);       
}

bool SendData_Wrist1_MotorByPressSensor(){
  static float Qk1=460;
  static float Qk=0;
  
  static float Pk1=460;
  static float Pk=0;
  
  const int analogInPin_Base_DIR0 = A8;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Base_DIR1 = A9;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Base_DIR0 = 0;        // value read from the pot
  int sensorValue_Base_DIR1 = 0;        // value read from the pot
  
  int outputValue_BaseSensor_DIR0 = 0; 
  int outputValue_BaseSensor_DIR1 = 0; 
   
    //send one new move
  //Direction0
  Qk= analogRead(analogInPin_Base_DIR0);
  Qk1=Qk1+Alpha*(Qk-Qk1);
  sensorValue_Base_DIR0 =int(Qk1);
  
  //Direction1    
  Pk = analogRead(analogInPin_Base_DIR1); 
  Pk1=Pk1+Alpha*(Pk-Pk1);
  sensorValue_Base_DIR1=Pk1;
    
  //Serial.println(Qk);
  
  // map it to the range of the analog out:
  outputValue_BaseSensor_DIR0 = map(sensorValue_Base_DIR0, 0, 380, 0, 99);  
  outputValue_BaseSensor_DIR1 = map(sensorValue_Base_DIR1, 0, 380, 0, 99);
   //Serial.println(Qk);
    //Motor On/Off Control
    if( Qk<360){       
            //outputValue_BaseSensor_DIR0=TimmerCounterPeriod+outputValue_BaseSensor_DIR0;
            String PeriodVal=String(int(outputValue_BaseSensor_DIR0));
            PeriodVal+="e;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);       
           return true;         
    }   
  
    if(Pk<360){
            //outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
            outputValue_BaseSensor_DIR1=outputValue_BaseSensor_DIR1*-1;
            String PeriodVal=String(outputValue_BaseSensor_DIR1);
            PeriodVal+="e;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
    
          return true;        
    }
    
    return false;
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void DecideSending_Wrist2_DataByENA(){
  
   if( digitalRead(Wrist2_MotorControENAPin)==0){ //  
       return;               
   }
   
   //Detecting receiving
   if(SendData_Wrist2_MotorByPressSensor()==true){         
     while(digitalRead(Wrist2_MotorControENAPin)==1){}
   }
   //delay(500);       
}

bool SendData_Wrist2_MotorByPressSensor(){
  static float Qk1=460;
  static float Qk=0;
  
  static float Pk1=460;
  static float Pk=0;
  
  const int analogInPin_Base_DIR0 = A10;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Base_DIR1 = A11;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Base_DIR0 = 0;        // value read from the pot
  int sensorValue_Base_DIR1 = 0;        // value read from the pot
  
  int outputValue_BaseSensor_DIR0 = 0; 
  int outputValue_BaseSensor_DIR1 = 0; 
   
    //send one new move
  //Direction0
  Qk= analogRead(analogInPin_Base_DIR0);
  Qk1=Qk1+Alpha*(Qk-Qk1);
  sensorValue_Base_DIR0 =int(Qk1);
  
  //Direction1    
  Pk = analogRead(analogInPin_Base_DIR1); 
  Pk1=Pk1+Alpha*(Pk-Pk1);
  sensorValue_Base_DIR1=Pk1;
    
  //Serial.println(Qk);
  
  // map it to the range of the analog out:
  outputValue_BaseSensor_DIR0 = map(sensorValue_Base_DIR0, 0, 380, 0, 99);  
  outputValue_BaseSensor_DIR1 = map(sensorValue_Base_DIR1, 0, 380, 0, 99);
   //Serial.println(Qk);
    //Motor On/Off Control
    if( Qk<360){       
            //outputValue_BaseSensor_DIR0=TimmerCounterPeriod+outputValue_BaseSensor_DIR0;
            String PeriodVal=String(int(outputValue_BaseSensor_DIR0));
            PeriodVal+="f;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);       
           return true;         
    }   
  
    if(Pk<360){
            //outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
            outputValue_BaseSensor_DIR1=outputValue_BaseSensor_DIR1*-1;
            String PeriodVal=String(outputValue_BaseSensor_DIR1);
            PeriodVal+="f;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
    
          return true;        
    }
    
    return false;
}



void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);  
  pinMode(Base_MotorControENAPin, INPUT);  
  pinMode(UpArm_MotorControENAPin,INPUT);
  pinMode(Elbow_MotorControENAPin,INPUT);
  pinMode(WristBase_MotorControENAPin,INPUT);
  pinMode(Wrist1_MotorControENAPin,INPUT);
  pinMode(Wrist2_MotorControENAPin,INPUT);

}

void loop() // run over and over
{   
 
  DecideSending_UpArm_DataByENA(); 
  DecideSending_Base_DataByENA();    
  DecideSending_Elbow_DataByENA();
  DecideSending_WristBase_DataByENA();
  DecideSending_Wrist1_DataByENA();
  DecideSending_Wrist2_DataByENA();
}

/*
void DecideSending_Base_DataByENA2(){
    //If nano stepper is moving, only send ONE new move    
    static int countingSendingTimes=0;
    
   if( digitalRead(Base_MotorControENAPin)==1){ 
     if(countingSendingTimes==0){
       countingSendingTimes=1;

       if(SendData_BaseMotorByPressSensor()==false){ //for invalid sensor value
         countingSendingTimes=0;
       }
     }     
     
   }else{
     if(countingSendingTimes==1){  
       countingSendingTimes=1;                       
       if(SendData_BaseMotorByPressSensor()==false){ //for invalid sensor value
            countingSendingTimes=0;
       }
       
     }
     
   }

}
*/
