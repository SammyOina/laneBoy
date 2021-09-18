double I = 0;
int linePosition[5];
int steeringPosition(int error, int lastError){   //get control position to compensate for
  double kp = 0.78;     //PID gains
  int ki = 0;
  double kd = 1;
  double P = error * kp;
  I = (I+error)* ki;
  double D = (error - lastError) * kd;
  lastError = error;
  return  P + I + D;
}
void initializeIRSesors(){
  pinMode(A1, INPUT);     // set pin modes
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}
int getPosition(int previousPos){                   //get position of the line
  linePosition[0] = 1 - digitalRead(A1);            //read infrared reflectance sensors
  linePosition[1] = 1 - digitalRead(A2);
  linePosition[2] = 1 - digitalRead(A3);
  linePosition[3] = 1 - digitalRead(A4);
  linePosition[4] = 1 - digitalRead(A5);
  if (linePosition[0] == 0 && linePosition[1] == 0 && linePosition[2] == 0 && linePosition[3] == 0 && linePosition[4] == 0){
    return previousPos;                             //in case line is lost then use the previous position
  }else{
    int position = (linePosition[0] * 180 + linePosition[1] * 135 + linePosition[2] * 90 + linePosition[3] * 45 + linePosition[4] * 0)/
    (linePosition[0] + linePosition[1] + linePosition[2] + linePosition[3] + linePosition[4]);
    return position;                              //return line position
  }
}
