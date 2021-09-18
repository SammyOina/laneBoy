int ENB = 2;
int IN3 = 0;
int IN4 = 1;
int ENA = 8;
int IN1 = 7;
int IN2 = 6;
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
