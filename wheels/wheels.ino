//defining pins and variables
#define lefts A0
#define rights A1
#define motorR1 3
#define motorR2 5
#define motorL1 9
#define motorL2 10
 
void setup() 
{ 
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);

  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(lefts));
  Serial.println(analogRead(rights));
  //line detected by both
  if(analogRead(lefts)<=400 && analogRead(rights)<=400){
    //nothing
    analogWrite(motorR1, 125);
    analogWrite(motorR2, 125);
    analogWrite(motorL1, 125);
    analogWrite(motorL2, 125);
  }
  //line detected by left sensor
  else if(analogRead(lefts)<=400 && !analogRead(rights)<=400){
    //turn left
    analogWrite(motorR1, 240);
    analogWrite(motorR2, 240);
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 0);
  }
  //line detected by right sensor
  else if(!analogRead(lefts)<=400 && analogRead(rights)<=400){
    //turn right
    analogWrite(motorR1, 0);
    analogWrite(motorR2, 0);
    analogWrite(motorL1, 240);
    analogWrite(motorL2, 240);
  }
  //line detected by none
  else if(!analogRead(lefts)<=400 && !analogRead(rights)<=400){
    analogWrite(motorR1, 125);
    analogWrite(motorR2, 125);
    analogWrite(motorL1, 125);
    analogWrite(motorL2, 125);
  }
}
