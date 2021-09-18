#include "motorControl.h"
#include "positions.h"
int pos = 0;
int motorSpeedA = 255;
int motorSpeedB = 255;
int currentPosition;
double error;
double lastError = 0;
int exceptS =0;
int previousPos = 90;
void setup() {
  Serial.begin(9600);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ENB, LOW);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(ENA, LOW);
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
