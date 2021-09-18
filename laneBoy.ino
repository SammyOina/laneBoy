int pos = 0;
int



motorSpeedA = 255;
int motorSpeedB = 255;
int ENB = 2;
int IN3 = 0;
int IN4 = 1;
int ENA = 8;
int IN1 = 7;
int IN2 = 6;
int linePosition[5];
int currentPosition;
double error;
double I = 0;
double lastError = 0;
int exceptS =0;
int previousPos = 90;
void driveForever(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void brakeMyFall(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
int steeringPosition(int error){
  double kp = 0.78;
  int ki = 0;
  double kd = 1;
  double P = error * kp;
  I = (I+error)* ki;
  double D = (error - lastError) * kd;
  lastError = error;
  return  P + I + D;
}
int getPosition(){
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  linePosition[0] = 1 - digitalRead(A1);
  linePosition[1] = 1 - digitalRead(A2);
  linePosition[2] = 1 - digitalRead(A3);
  linePosition[3] = 1 - digitalRead(A4);
  linePosition[4] = 1 - digitalRead(A5);
  if (linePosition[0] == 0 && linePosition[1] == 0 && linePosition[2] == 0 && linePosition[3] == 0 && linePosition[4] == 0){
    return previousPos;
  }else{
    int position = (linePosition[0] * 180 + linePosition[1] * 135 + linePosition[2] * 90 + linePosition[3] * 45 + linePosition[4] * 0)/
    (linePosition[0] + linePosition[1] + linePosition[2] + linePosition[3] + linePosition[4]);
    return position;
  }
}
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
  currentPosition = getPosition();
  /*if (currentPosition != previousPos){
    brakeMyFall();
    delay(30);
  }
  driveForever();*/
  previousPos = currentPosition;
  error = 90 - currentPosition;
  motorSpeedA = constrain(100 + steeringPosition(error), 0, 100);
  motorSpeedB = constrain(100 - steeringPosition(error), 0, 100);
  Serial.println(motorSpeedB);
  analogWrite(ENB, motorSpeedB);
  analogWrite(ENA, motorSpeedA);  
}
