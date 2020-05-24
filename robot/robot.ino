//Wheels
#include <CheapStepper.h>
CheapStepper right (6,7,8,9); 
CheapStepper left (10,11,12,13); 

//Pump
#define pumpDir 2
#define pumpStep 3
#define stepsPerRevolution 800
#include <Stepper.h>
Stepper p(stepsPerRevolution,2,3);


//Servo
#define servo 4
#include <Servo.h> 
Servo Arm; 

//Sensors
#define IR_Left A4
#define IR_Right A5 
#define waterSensor A0
#define moistureSensor A1

int totalPlants = 5;
int currentPlant = 0;

void setup() {
  right.setRpm(20); 
  left.setRpm(20);
  
  pinMode(pumpStep, OUTPUT);
  pinMode(pumpDir, OUTPUT);

  Arm.attach(servo); 
  Arm.write(0);

  p.setSpeed(250);
  
  Serial.begin(9600);
}

void loop() {
  int water_level = analogRead(waterSensor);
  Serial.println(water_level);
  if(water_level < 100){
    Serial.println("No water");
    returnHome();
  } else {
    moveOn();
    visitPlant();
  }
}

void moveOn(){
  while(!plantNearby()){
    drive(true);
  } 
}

void visitPlant(){
  turnLeft();
  while(!plantNearby()){
    drive(true);
  }
  waterPlant();
  currentPlant += 1;
  while(!plantNearby()){
    drive(false);
  }
  turnBackToLine();
}

void waterPlant(){
  int moisture = analogRead(moistureSensor);
  lowerArm();
  while(moisture < 300){
    pump();
    moisture = analogRead(moistureSensor);
  }
  liftArm();
}

void pump(){
  p.step(stepsPerRevolution);
}

bool plantNearby(){
  return (analogRead(IR_Left) < 500 && analogRead(IR_Right) < 500);
}

void drive(bool forward){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(IR_Left));
  Serial.println(analogRead(IR_Right));
  
  if(analogRead(IR_Left) > 500 && analogRead(IR_Right) < 500){
    right.move(forward, 20);
  } else if(analogRead(IR_Left) < 500 && analogRead(IR_Right) > 500){
    left.move(forward, 20);
  } else if(analogRead(IR_Left) > 500 && analogRead(IR_Right) > 500){
    right.move(forward, 20);
    left.move(forward, 20);
  }
}

void turnLeft(){
  right.move(false, 4000);
  delay(1000);  
}

void turnRight(){
  left.move(false, 4000);
  delay(1000);  
}

void turnBackToLine(){
  right.move(true, 4000);
  delay(1000); 
}

void lowerArm(){ 
  Arm.write(45); 
  delay(1000); 
}

void liftArm(){
  Arm.write(0); 
  delay(1000);
}

void returnHome(){
  //drive past remaining plant
  while(currentPlant < totalPlants){
    while(!plantNearby){ drive(true); }
    currentPlant += 1;
  }
  //drive until we meet the watertower
  while(!plantNearby()){
    drive(true);
  }
  turnRight();
  reload();
}

void reload(){
  int water_level = analogRead(waterSensor);
  while(water_level > 600){
    drive(false);
    water_level = analogRead(waterSensor);
  }
  while(!plantNearby()){
    drive(true);
  }
  turnLeft();
}
