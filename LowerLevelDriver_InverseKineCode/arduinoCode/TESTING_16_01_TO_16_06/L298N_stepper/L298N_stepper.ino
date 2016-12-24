
int Pin0 = 19;
int Pin1 = 8;
int Pin2 = 12;
int Pin3 = 13;
int _step =0 ;
boolean dir; //= -1;正反转
int stepperSpeed = 10;//电机转速,1ms一步
void setup()
{
  pinMode(Pin0, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(4,INPUT);
}

void loop()
{
  for(int i=0;i<=5000;i++){

  down();
  } 
  for(int i=0;i<=5000;i++){
 
  up();
  }

}

void down()
  {
   
    switch(_step){
    case 0:
    //stepperSpeed++;
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);//32A
    break;
    case 1:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);//10B
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
    break;
    case 2:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
    case 3:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
    case 4:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
    case 5:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
      case 6:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
    case 7:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
    break;
    default:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
  }
   _step++;
 
  if(_step>7){    _step=0;  }

  delay(stepperSpeed);
  } 
    
     
    
  void up()
{ 
  
  switch(_step){
    case 0:
    //stepperSpeed++;
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);//32A
    break;
    case 1:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);//10B
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
    case 2:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
    case 3:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
    case 4:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
    case 5:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
    break;
      case 6:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
    break;
    case 7:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
    break;
    default:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
  }
    _step++;
 
  if(_step>7){    _step=0;  }
 
  delay(stepperSpeed);

}

