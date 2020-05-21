#include <CheapStepper.h>

// next, declare the stepper

CheapStepper right (6,7,8,9); 
CheapStepper left (10,11,12,13); 

 // let's create a boolean variable to save the direction of our rotation

boolean moveClockwise = true;

void setup() {

  // let's set a custom speed of 20rpm (the default is ~16.25rpm)
  
  right.setRpm(20); 
  left.setRpm(20); 
  /* Note: CheapStepper library assumes you are powering your 28BYJ-48 stepper
   * using an external 5V power supply (>100mA) for RPM calculations
   * -- don't try to power the stepper directly from the Arduino
   * accepted RPM range: 6RPM (may overheat) - 24RPM (may skip)
   * ideal range: 10RPM (safe, high torque) - 22RPM (fast, low torque)
   */

  // now let's set up a serial connection and print some stepper info to the console
  
  Serial.begin(9600); 
}

void loop() {
    right.move(moveClockwise, 4096);
    left.move(moveClockwise, 4096);

    delay(1000);  
}
