

const float Alpha=0.1;

const int Base_MotorControENAPin = 8;     // the number of the pushbutton pin
const int UpArm_MotorControENAPin = 9;     // the number of the pushbutton pin
const int Elbow_MotorControENAPin = 10;     // the number of the pushbutton pin
const int WristBase_MotorControENAPin = 11;     // 
const int Wrist1_MotorControENAPin = 12;     // 
const int Wrist2_MotorControENAPin = 13;     // 

/************PRESURE SENSOR CONTROL STEPPER SETUP********/
/********************************************************/

int MySensorStepMap(int inputVal){
  
  if(inputVal<200){
  return 600;
  }
  if(inputVal>600){
    return 1;
    }

  return 600-map(inputVal, 200, 600, 1, 599);  
}
/////////////////////////////////////////////////////////

bool SendData_Base_MotorByPressSensor(){
  
  const int analogInPin_Base_DIR0 = A0;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Base_DIR1 = A1;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Base_DIR0 = 0;        // value read from the pot
  int sensorValue_Base_DIR1 = 0;        // value read from the pot

    //send one new move
  //Direction0
  sensorValue_Base_DIR0= analogRead(analogInPin_Base_DIR0);
  sensorValue_Base_DIR0 =int(sensorValue_Base_DIR0);
  
  //Direction1    
  sensorValue_Base_DIR1= analogRead(analogInPin_Base_DIR1); 
  sensorValue_Base_DIR1=int(sensorValue_Base_DIR1);
  
   //Serial.println(Qk);
    //Motor On/Off Control
    if( sensorValue_Base_DIR0<=600){       
            //outputValue_BaseSensor_DIR0=TimmerCounterPeriod+outputValue_BaseSensor_DIR0;
            sensorValue_Base_DIR0=MySensorStepMap(sensorValue_Base_DIR0);
            String PeriodVal=String(int(sensorValue_Base_DIR0));
            PeriodVal+="A;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal); 
            Serial2.print(PeriodVal);      
            return true;
          
    }   
  
    if(sensorValue_Base_DIR1<600){
            //outputValue_BaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_BaseSensor_DIR1)*2;
            sensorValue_Base_DIR1=MySensorStepMap(sensorValue_Base_DIR1);
            sensorValue_Base_DIR1=sensorValue_Base_DIR1*-1;
            String PeriodVal=String(sensorValue_Base_DIR1);
            PeriodVal+="A;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
            Serial2.print(PeriodVal);
    
          return true;        
    }
    
    return false;  
}
/////////////////////////////////////////////////////////////
bool SendData_UpArm_MotorByPressSensor(){
  
  const int analogInPin_UpArm_DIR0 = A2;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_UpArm_DIR1 = A3;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_UpArm_DIR0 = 0;        // value read from the pot
  int sensorValue_UpArm_DIR1 = 0;        // value read from the pot

    //send one new move
  //Direction0
  sensorValue_UpArm_DIR0= analogRead(analogInPin_UpArm_DIR0);
  sensorValue_UpArm_DIR0 =int(sensorValue_UpArm_DIR0);
  
  //Direction1    
  sensorValue_UpArm_DIR1 = analogRead(analogInPin_UpArm_DIR1); 
  sensorValue_UpArm_DIR1=int(sensorValue_UpArm_DIR1);
  
   //Serial.println(Qk);
    //Motor On/Off Control
    if( sensorValue_UpArm_DIR0<=600){       
            //outputValue_UpArmSensor_DIR0=TimmerCounterPeriod+outputValue_UpArmSensor_DIR0;
            sensorValue_UpArm_DIR0=MySensorStepMap(sensorValue_UpArm_DIR0);
            String PeriodVal=String(int(sensorValue_UpArm_DIR0));
            PeriodVal+="B;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);   
            Serial2.print(PeriodVal);    
            return true;
          
    }   
  
    if(sensorValue_UpArm_DIR1<600){
            //outputValue_UpArmSensor_DIR1=TimmerCounterPeriod+(99-outputValue_UpArmSensor_DIR1)*2;
            sensorValue_UpArm_DIR1=MySensorStepMap(sensorValue_UpArm_DIR1);
            sensorValue_UpArm_DIR1=sensorValue_UpArm_DIR1*-1;
            String PeriodVal=String(sensorValue_UpArm_DIR1);
            PeriodVal+="B;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
            Serial2.print(PeriodVal);
    
          return true;        
    }
    
    return false;  
}

//////////////////////////////////////////////////
bool SendData_Elbow_MotorByPressSensor(){
  
  const int analogInPin_Elbow_DIR0 = A4;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Elbow_DIR1 = A5;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Elbow_DIR0 = 0;        // value read from the pot
  int sensorValue_Elbow_DIR1 = 0;        // value read from the pot

    //send one new move
  //Direction0
  sensorValue_Elbow_DIR0= analogRead(analogInPin_Elbow_DIR0);
  sensorValue_Elbow_DIR0 =int(sensorValue_Elbow_DIR0);
  
  //Direction1    
  sensorValue_Elbow_DIR1= analogRead(analogInPin_Elbow_DIR1); 
  sensorValue_Elbow_DIR1=int(sensorValue_Elbow_DIR1);
  
   //Serial.println(Qk);
    //Motor On/Off Control
    if( sensorValue_Elbow_DIR0<=600){       
            //outputValue_ElbowSensor_DIR0=TimmerCounterPeriod+outputValue_ElbowSensor_DIR0;
            sensorValue_Elbow_DIR0=MySensorStepMap(sensorValue_Elbow_DIR0);
            String PeriodVal=String(int(sensorValue_Elbow_DIR0));
            PeriodVal+="C;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);   
            Serial2.print(PeriodVal);    
            return true;
          
    }   
  
    if(sensorValue_Elbow_DIR1<600){
            //outputValue_ElbowSensor_DIR1=TimmerCounterPeriod+(99-outputValue_ElbowSensor_DIR1)*2;
            sensorValue_Elbow_DIR1=MySensorStepMap(sensorValue_Elbow_DIR1);
            sensorValue_Elbow_DIR1=sensorValue_Elbow_DIR1*-1;
            String PeriodVal=String(sensorValue_Elbow_DIR1);
            PeriodVal+="C;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
            Serial2.print(PeriodVal);
    
          return true;        
    }
    
    return false;  
}
///////////////////////////////////////////////////////////////


bool SendData_WristBase_MotorByPressSensor(){
  
  const int analogInPin_WristBase_DIR0 = A6;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_WristBase_DIR1 = A7;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_WristBase_DIR0 = 0;        // value read from the pot
  int sensorValue_WristBase_DIR1 = 0;        // value read from the pot

    //send one new move
  //Direction0
  sensorValue_WristBase_DIR0= analogRead(analogInPin_WristBase_DIR0);
  sensorValue_WristBase_DIR0 =int(sensorValue_WristBase_DIR0);
  
  //Direction1    
  sensorValue_WristBase_DIR1= analogRead(analogInPin_WristBase_DIR1); 
  sensorValue_WristBase_DIR1=int(sensorValue_WristBase_DIR1);
  
   //Serial.println(Qk);
    //Motor On/Off Control
    if( sensorValue_WristBase_DIR0<=600){       
            //outputValue_WristBaseSensor_DIR0=TimmerCounterPeriod+outputValue_WristBaseSensor_DIR0;
            sensorValue_WristBase_DIR0=MySensorStepMap(sensorValue_WristBase_DIR0);
            String PeriodVal=String(int(sensorValue_WristBase_DIR0));
            PeriodVal+="D;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);
            Serial2.print(PeriodVal);       
            return true;
          
    }   
  
    if(sensorValue_WristBase_DIR1<600){
            //outputValue_WristBaseSensor_DIR1=TimmerCounterPeriod+(99-outputValue_WristBaseSensor_DIR1)*2;
            sensorValue_WristBase_DIR1=MySensorStepMap(sensorValue_WristBase_DIR1);
            sensorValue_WristBase_DIR1=sensorValue_WristBase_DIR1*-1;
            String PeriodVal=String(sensorValue_WristBase_DIR1);
            PeriodVal+="D;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
            Serial2.print(PeriodVal);
    
          return true;        
    }
    
    return false;  
}

///////////////////////////////////////////////////////////////////////////

bool SendData_Wrist1_MotorByPressSensor(){
  
  const int analogInPin_Wrist1_DIR0 = A8;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Wrist1_DIR1 = A9;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Wrist1_DIR0 = 0;        // value read from the pot
  int sensorValue_Wrist1_DIR1 = 0;        // value read from the pot

    //send one new move
  //Direction0
  sensorValue_Wrist1_DIR0= analogRead(analogInPin_Wrist1_DIR0);
  sensorValue_Wrist1_DIR0 =int(sensorValue_Wrist1_DIR0);
  
  //Direction1    
  sensorValue_Wrist1_DIR1= analogRead(analogInPin_Wrist1_DIR1); 
  sensorValue_Wrist1_DIR1=int(sensorValue_Wrist1_DIR1);
  
   //Serial.println(Qk);
    //Motor On/Off Control
    if( sensorValue_Wrist1_DIR0<=600){       
            //outputValue_Wrist1Sensor_DIR0=TimmerCounterPeriod+outputValue_Wrist1Sensor_DIR0;
            sensorValue_Wrist1_DIR0=MySensorStepMap(sensorValue_Wrist1_DIR0);
            String PeriodVal=String(int(sensorValue_Wrist1_DIR0));
            PeriodVal+="E;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);   
            Serial2.print(PeriodVal);    
            return true;
          
    }   
  
    if(sensorValue_Wrist1_DIR1<600){
            //outputValue_Wrist1Sensor_DIR1=TimmerCounterPeriod+(99-outputValue_Wrist1Sensor_DIR1)*2;
            sensorValue_Wrist1_DIR1=MySensorStepMap(sensorValue_Wrist1_DIR1);
            sensorValue_Wrist1_DIR1=sensorValue_Wrist1_DIR1*-1;
            String PeriodVal=String(sensorValue_Wrist1_DIR1);
            PeriodVal+="E;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
            Serial2.print(PeriodVal);
    
          return true;        
    }
    
    return false;  
}


///////////////////////////////////////////////////

bool SendData_Wrist2_MotorByPressSensor(){
  
  const int analogInPin_Wrist2_DIR0 = A10;  // Analog input pin that the potentiometer is attached to
  const int analogInPin_Wrist2_DIR1 = A11;  // Analog input pin that the potentiometer is attached to
  
  int sensorValue_Wrist2_DIR0 = 0;        // value read from the pot
  int sensorValue_Wrist2_DIR1 = 0;        // value read from the pot

    //send one new move
  //Direction0
  sensorValue_Wrist2_DIR0= analogRead(analogInPin_Wrist2_DIR0);
  sensorValue_Wrist2_DIR0 =int(sensorValue_Wrist2_DIR0);
  
  //Direction1    
  sensorValue_Wrist2_DIR1= analogRead(analogInPin_Wrist2_DIR1); 
  sensorValue_Wrist2_DIR1=int(sensorValue_Wrist2_DIR1);
  
   //Serial.println(Qk);
    //Motor On/Off Control
    if( sensorValue_Wrist2_DIR0<=600){       
            //outputValue_Wrist2Sensor_DIR0=TimmerCounterPeriod+outputValue_Wrist2Sensor_DIR0;
            sensorValue_Wrist2_DIR0=MySensorStepMap(sensorValue_Wrist2_DIR0);
            String PeriodVal=String(int(sensorValue_Wrist2_DIR0));
            PeriodVal+="F;";  
            
           // mySerial.print(PeriodVal);             
            Serial.print(PeriodVal);  
            Serial2.print(PeriodVal);     
            return true;
          
    }   
  
    if(sensorValue_Wrist2_DIR1<600){
            //outputValue_Wrist2Sensor_DIR1=TimmerCounterPeriod+(99-outputValue_Wrist2Sensor_DIR1)*2;
            sensorValue_Wrist2_DIR1=MySensorStepMap(sensorValue_Wrist2_DIR1);
            sensorValue_Wrist2_DIR1=sensorValue_Wrist2_DIR1*-1;
            String PeriodVal=String(sensorValue_Wrist2_DIR1);
            PeriodVal+="F;";       
            //mySerial.print(PeriodVal);    
            Serial.print(PeriodVal); 
            Serial2.print(PeriodVal);
    
          return true;        
    }
    
    return false;  
}

void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);  
  Serial2.begin(9600);  
  pinMode(Base_MotorControENAPin, INPUT);  
  pinMode(UpArm_MotorControENAPin,INPUT);
  pinMode(Elbow_MotorControENAPin,INPUT);
  pinMode(WristBase_MotorControENAPin,INPUT);
  pinMode(Wrist1_MotorControENAPin,INPUT);
  pinMode(Wrist2_MotorControENAPin,INPUT);

}

void loop() // run over and over
{   
 
SendData_Base_MotorByPressSensor();
SendData_UpArm_MotorByPressSensor();

SendData_Elbow_MotorByPressSensor();
SendData_WristBase_MotorByPressSensor();
SendData_Wrist1_MotorByPressSensor();
SendData_Wrist2_MotorByPressSensor();
delay(50);
}

