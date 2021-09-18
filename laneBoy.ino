#include "motorControl.h"
#include "positions.h"
int pos = 0;
int motorSpeedA = 255;
int motorSpeedB = 255;
int currentPosition;
double error;
double lastError = 0;
int previousPos = 90;
void setup() {
  Serial.begin(9600);
  initializeMotors();
}

void loop() {
  currentPosition = getPosition(previousPos);
  if (currentPosition != previousPos){
    brakeMyFall();
    delay(30);
  }
  driveForever();
  previousPos = currentPosition;
  error = 90 - currentPosition;
  motorSpeedA = constrain(100 + steeringPosition(error, lastError), 0, 100);
  motorSpeedB = constrain(100 - steeringPosition(error, lastError), 0, 100);
  Serial.println(motorSpeedB);
  analogWrite(ENB, motorSpeedB);
  analogWrite(ENA, motorSpeedA);  
}
