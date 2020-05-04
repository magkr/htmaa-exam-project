//Wheels
#define wheelR1 3
#define wheelR2 5
#define wheelL1 6
#define wheelL2 9

//Pump
#define pumpStep 11
#define pumpDir 12
#define stepsPerRevolution 400

//Servo
#define servo 10
#include <Servo.h> 
Servo Arm; 

//Sensors
#define IR_Left A0
#define IR_Right A1
#define waterSensor A2
#define moistureSensor A3

void setup() {
  pinMode(wheelR1, OUTPUT);
  pinMode(wheelR2, OUTPUT);
  pinMode(wheelL1, OUTPUT);
  pinMode(wheelL2, OUTPUT);
  
  pinMode(pumpStep, OUTPUT);
  pinMode(pumpDir, OUTPUT);

  Arm.attach(servo); 

  Serial.begin(9600);
}

void loop() {
  int water_level = analogRead(waterSensor);

  if(water_level < 100){
    Serial.println("No water");
    returnHome();
  } else {
    moveOn();
  }
}

void moveOn(){
  while(noPlantNearby()){
    drive();
  } 
  while(!makeConnection()){};
  waterPlant();
  analogWrite(wheelR1, 125);
  analogWrite(wheelR2, 125);
  analogWrite(wheelL1, 125);
  analogWrite(wheelL2, 125);
}

bool makeConnection(){
  int moisture = analogRead(moistureSensor);
  return (moisture != 0);
}

void waterPlant(){
  //lower arm
  int moisture = analogRead(moistureSensor);

  while(moisture < 100){
    pump();
    moisture = analogRead(moistureSensor);
  }
}

void pump(){
  // Set the spinning direction clockwise:
  digitalWrite(pumpDir, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(pumpStep, HIGH);
    delayMicroseconds(2000);
    digitalWrite(pumpStep, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);
}

bool noPlantNearby(){
  //some other color
  return !(analogRead(IR_Left)<= 300 && analogRead(IR_Right)<= 300);
}

void drive(){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(IR_Left));
  Serial.println(analogRead(IR_Right));
  //line detected by both
  if(analogRead(IR_Left)<=400 && analogRead(IR_Right)<=400){
    //nothing
    analogWrite(wheelR1, 240);
    analogWrite(wheelR2, 240);
    analogWrite(wheelL1, 0);
    analogWrite(wheelL2, 0);
  }
  //line detected by left sensor
  else if(analogRead(IR_Left)<=400 && !analogRead(IR_Right)<=400){
    //turn left
    analogWrite(wheelR1, 240);
    analogWrite(wheelR2, 240);
    analogWrite(wheelL1, 0);
    analogWrite(wheelL2, 0);
  }
  //line detected by right sensor
  else if(!analogRead(IR_Left)<=400 && analogRead(IR_Right)<=400){
    //turn right
    analogWrite(wheelR1, 0);
    analogWrite(wheelR2, 0);
    analogWrite(wheelL1, 240);
    analogWrite(wheelL2, 240);
  }
  //line detected by none
  else if(!analogRead(IR_Left)<=400 && !analogRead(IR_Right)<=400){
    analogWrite(wheelR1, 125);
    analogWrite(wheelR2, 125);
    analogWrite(wheelL1, 125);
    analogWrite(wheelL2, 125);
  }
}

void returnHome(){
  
}
