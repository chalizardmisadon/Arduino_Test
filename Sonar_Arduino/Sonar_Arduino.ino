#include <Servo.h>

// Servo setting
int minAngle = 23, maxAngle = 158;
int angle = minAngle, stepAngle = 1;

// Ultrasonic setting
int trig = 11, echo = 12;
int disOne, disTwo, disThree; // distance values
boolean badData = true;

Servo myServo;
void setup(){
  pinMode(trig, OUTPUT); // Sonar I/O
  pinMode(echo, INPUT);
  myServo.attach(9); // Servo I/O
  Serial.begin(9600); // Serial communication
}

void loop(){
  //if (0 < Serial.available()) myServo.write(Serial.parseInt());
  radar();
}

void radar(){
  badData = true;
  //delay(60);
  //disOne = readDistance();
  
  disTwo = 1000; // random filler value
  disThree = 1001; // randome filler value
  while (badData){
    disThree = disTwo;
    disTwo = disOne;
    delayMicroseconds(5800);
    disOne = readDistance();

    if ((disOne == disTwo)&&(disTwo == disThree)){
      badData = false;
    }
  }
  
  //disOne = max(disOne, disTwo); // choose further distance
  if (disOne == 0) disOne = 100; // 0 means max distance
  Serial.print(angle);
  Serial.print(":");
  Serial.println(disOne);
  sweep();
}

int readDistance(){
  delayMicroseconds(2); // delay to prevent ultrasensor overheat
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); // 10 uS to send signal
  digitalWrite(trig, LOW);

  // read signal using Ultrasonic
  return pulseIn(echo, HIGH, 5800) / 58; // cm = uS/58
}

void sweep(){
  if (angle < minAngle) stepAngle = 1;
  if (angle > maxAngle) stepAngle = -1;
  angle += stepAngle;
  myServo.write(angle);
}

