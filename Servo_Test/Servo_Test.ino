#include <Servo.h>

int microStep = 20, currentStep = 780;
int low = 780, high = 2180, mid = (low+high)/2;

Servo myservo;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //if (Serial.available() > 0) myservo.writeMicroseconds(Serial.parseInt());
  myservo.writeMicroseconds(currentStep);
  sweep();
}

void sweep(){
  if (currentStep <= low){
    microStep = 20;
    Serial.println("low");
  }
  if (currentStep >= high){
    microStep = -20;
    Serial.println("high");
  }
  currentStep += microStep;
  delay(20);
}

