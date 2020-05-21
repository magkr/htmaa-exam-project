//Wheels
#include <CheapStepper.h>
CheapStepper right (6,7,8,9); 
CheapStepper left (10,11,12,13); 
boolean clockwise = false;

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
  lowerArm();
  int moisture = analogRead(moistureSensor);
  Serial.println(moisture);
  /*
  while(true){
    for(int i = 0; i < 10; i++){
      pump();  
    }
    int moisture = analogRead(moistureSensor);
    Serial.println(moisture);
    
  }
  */
  /*
  int water_level = analogRead(waterSensor);
  Serial.println(water_level);
  if(water_level < 100){
    Serial.println("No water");
    returnHome();
  } else {
    moveOn();
    visitPlant();
  }
   */
  
}

void moveOn(){
  while(!plantNearby()){
    drive();
  } 
}

void visitPlant(){
  turnLeft();
  while(!plantNearby()){
    drive();
  }
  waterPlant();
  currentPlant += 1;
  while(!plantNearby()){
    reverse();
  }
  turnBackToLine();
}

void waterPlant(){
  //lower arm
  int moisture = 1; //analogRead(moistureSensor);
  lowerArm();
  while(moisture < 10){
    pump();
    moisture += 1; //analogRead(moistureSensor);
  }
  liftArm();
}

void pump(){
  p.step(stepsPerRevolution);
}

bool plantNearby(){
  //a line that meets 
  return (analogRead(IR_Left) < 500 && analogRead(IR_Right) < 500);
}

void drive(){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(IR_Left));
  Serial.println(analogRead(IR_Right));
  
  if(analogRead(IR_Left) > 500 && analogRead(IR_Right) < 500){
    right.move(clockwise, 20);
  } else if(analogRead(IR_Left) < 500 && analogRead(IR_Right) > 500){
    left.move(clockwise, 20);
  } else if(analogRead(IR_Left) > 500 && analogRead(IR_Right) > 500){
    right.move(clockwise, 20);
    left.move(clockwise, 20);
  }
}

void reverse(){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(IR_Left));
  Serial.println(analogRead(IR_Right));
  
  if(analogRead(IR_Left) > 500 && analogRead(IR_Right) < 500){
    right.move(!clockwise, 20);
  } else if(analogRead(IR_Left) < 500 && analogRead(IR_Right) > 500){
    left.move(!clockwise, 20);
  } else if(analogRead(IR_Left) > 500 && analogRead(IR_Right) > 500){
    right.move(!clockwise, 20);
    left.move(!clockwise, 20);
  }
}

void turnLeft(){
  right.move(clockwise, 4000);
  delay(1000);  
}

void turnBackToLine(){
  right.move(!clockwise, 4000);
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
  while(currentPlant < totalPlants){
    while(!plantNearby){ drive(); }
    currentPlant += 1;
  }
  reload();
}

void reload(){
    
}
