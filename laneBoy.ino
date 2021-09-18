#include "motorControl.h"
#include "positions.h"
#define MAX_SPEED 100
#define MINIMUM_SPEED 0
int motorSpeedA;
int motorSpeedB;
int currentPosition;
double error;
double lastError = 0;
int previousPos = 90;                 //set starting previous position to centre of the line
void setup() {
  Serial.begin(9600);
  initializeMotors();
  initializeIRSesors();
}

void loop() {
  currentPosition = getPosition(previousPos);
  if (currentPosition != previousPos){    //brake in case of change in line psotion
    brake();
    delay(30);                            // beaking time for more precision
  }
  drive();                                //set motors to drive
  previousPos = currentPosition;
  error = 90 - currentPosition;           //get error in deviation from the line
  motorSpeedA = constrain(MAX_SPEED + steeringPosition(error, lastError), MINIMUM_SPEED, MAX_SPEED);  //set motor speeds
  motorSpeedB = constrain(MAX_SPEED - steeringPosition(error, lastError), MINIMUM_SPEED, MAX_SPEED);
  analogWrite(ENB, motorSpeedB);          //write motor speeds
  analogWrite(ENA, motorSpeedA);  
}
