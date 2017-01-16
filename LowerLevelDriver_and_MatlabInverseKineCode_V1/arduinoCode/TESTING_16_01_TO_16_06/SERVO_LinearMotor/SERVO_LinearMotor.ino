
//SERVO LINEAR MOTOR
int MotorIn1 = 9;     
int MotorIn2 = 10;     

// the setup routine runs once when you press reset:
void setup() { 
  Serial.begin(9600); 
  SETUP_LinearMotor();
}

// the loop routine runs over and over again forever:
void loop() {
  MotorServo(5);

}

void SETUP_LinearMotor(){
  pinMode(MotorIn1, OUTPUT);
  pinMode(MotorIn2,OUTPUT); 
 
  }

float MotorServo(float Desired_position){
  //Return: Valtage in mV. 
  // Parameter: Desired_position: where you want it be
    
  
  
  // Move to given position
  // potential meter range: 0-57mm
  // voltage range: 0-5000mV => 5000mV/57mm=87.7=88mV/mm
  // safe range: 2mm-57mm => 200mV-5000mV
  if(Desired_position<2) Desired_position=2.0;
  if(Desired_position>57) Desired_position=57.0; 

  //(5000mV/57mm)*targetPosition
  float target_mV=(5000.0/57.0)*Desired_position; 

  float sensorValue = analogRead(A0);
  float voltage_mv = sensorValue * (5.0 / 1023.0)*1000;
  float error= target_mV-voltage_mv ; 
  Serial.println(voltage_mv);

  if(abs(error)<=5){
     ResetMotorPin();
    return voltage_mv ;
    }
  
  // if error less than 44mV( 0.5mm), done
  while(abs(error)>3){
 
    
    if(error>0){
      MovingShorter();      
      }
    else{
      MovingLonger();     
      }  

    sensorValue = analogRead(A0);
    voltage_mv = sensorValue * (5.0 / 1023.0)*1000;
    error= target_mV-voltage_mv;
    Serial.println(voltage_mv);

    /*
    ServoFakeSpeed(10); //control speed
    ResetMotorPin();
    ServoFakeSpeed(10);*/
    }
    
   Serial.println(voltage_mv);
   ResetMotorPin();
  return voltage_mv;
  
  }

void MovingShorter(){
  //SHORTER
  digitalWrite(MotorIn2, LOW);
  digitalWrite(MotorIn1, HIGH);  
  }

void MovingLonger(){
  //LONGER
 digitalWrite(MotorIn2, HIGH);
 digitalWrite(MotorIn1,LOW ); 
  }

void ServoFakeSpeed(int speed){
  delay(speed);
  }

void ResetMotorPin(){
  pinMode(MotorIn1, INPUT);
  pinMode(MotorIn2,INPUT);   
  pinMode(MotorIn1, OUTPUT);
  pinMode(MotorIn2,OUTPUT);
  pinMode(MotorIn1, LOW);
  pinMode(MotorIn2,LOW);
  }    
