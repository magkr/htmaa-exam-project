//defining pins and variables
#define lefts A4
#define rights A5
#define motorR 5
#define motorL 6


void setup() {
  //declaring pin types
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  
  //begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(lefts));
  Serial.println(analogRead(rights));
  //line detected by both
  if(analogRead(lefts)<=400 && analogRead(rights)<=400){
    //nothing
    analogWrite(motorR, 125);
    analogWrite(motorL, 125);
  }
  //line detected by left sensor
  else if(analogRead(lefts)<=400 && !analogRead(rights)<=400){
    //turn left

    analogWrite(motorR, 240);
    analogWrite(motorL, 0);
    delay(200);
  }
  //line detected by right sensor
  else if(!analogRead(lefts)<=400 && analogRead(rights)<=400){
    //turn right
 
    analogWrite(motorL, 240);
    analogWrite(motorR, 0);
    delay(200);
  }
  //line detected by none
  else if(!analogRead(lefts)<=400 && !analogRead(rights)<=400){
    //stop
    analogWrite(motorR, 125);
    analogWrite(motorL, 125);
  }
  
}
