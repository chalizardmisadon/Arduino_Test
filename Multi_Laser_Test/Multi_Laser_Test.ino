#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1, sensor2, sensor3;
int ShutPin1 = 13, ShutPin2 = 12, ShutPin3 = 8;
int leftForward = 6, leftBackward = 9, rightForward = 10, rightBackward = 11;
byte lineSensor = 0, rangeSensor = 0;

//==================== Start of Miscelaneous ====================
void startWait(){
  Serial.println("Program Stall");
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  pinMode(1, INPUT);
  while (digitalRead(1) == LOW){
    Serial.println("Stall...");
    delay(100);
  }
  Serial.println("Program Start");
  delay(4500);
}
//==================== End of Miscelaneous ====================
//==================== Start of Motor Control ====================
void initMotor(){
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);
}

void turnLeft(){
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
  delay(1000);
  digitalWrite(rightBackward, LOW);
  digitalWrite(rightForward, HIGH);
  delay(1000);
}

void turnRight(){
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
  delay(1000);
  digitalWrite(leftBackward, LOW);
  digitalWrite(leftForward, HIGH);
  delay(1000);
}

void goForward(){
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
  digitalWrite(leftForward, HIGH);
  digitalWrite(rightForward, HIGH);
}


//==================== End of Motor Control ====================
//==================== Start of RangeFinder ====================
void XShut(int pin){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(1);
}

void initSensor(int pin, VL53L0X sensor, uint8_t address ){
  pinMode(pin, INPUT);
  sensor.init(true);
  delay(100);
  sensor.setAddress(address);
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void scanForSensor(){
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
  
  for (byte i = 1; i < 120; i++){
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0){
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
    } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");

  delay(3000);
}

bool checkSensor(VL53L0X rangeFinder){
  int range = rangeFinder.readRangeContinuousMillimeters();
  if (2 < range && range < 100){
    return true;
  } else {
    return false;
  }
}

void scanSensor(){
  rangeSensor = 0;
  bitWrite(rangeSensor, 1, checkSensor(sensor1));
  bitWrite(rangeSensor, 2, checkSensor(sensor2));
  bitWrite(rangeSensor, 3, checkSensor(sensor3));

  switch (rangeSensor){
    case 0b1000:
      digitalWrite(rightBackward, LOW);
      digitalWrite(rightForward, HIGH);
      digitalWrite(leftForward, LOW);
      digitalWrite(leftBackward, HIGH);
    break;
    case 0b1100:
      digitalWrite(rightBackward, LOW);
      digitalWrite(rightForward, HIGH);
      digitalWrite(leftForward, LOW);
      digitalWrite(leftBackward, LOW);
    break;
    case 0b0100:
      digitalWrite(leftBackward, LOW);
      digitalWrite(leftForward, HIGH);
      digitalWrite(rightBackward, LOW);
      digitalWrite(rightForward, HIGH);
    break;
    case 0b0110:
      digitalWrite(leftBackward, LOW);
      digitalWrite(leftForward, HIGH);
      digitalWrite(rightBackward, LOW);
      digitalWrite(rightForward, LOW);
    break;
    case 0b0010:
      digitalWrite(leftBackward, LOW);
      digitalWrite(leftForward, HIGH);
      digitalWrite(rightForward, LOW);
      digitalWrite(rightBackward, HIGH);
    break;
  }
}
//==================== End of RangeFinder ====================
//==================== Start of LineSensor ====================
bool edgeDetect(int pin) {
  return analogRead(pin) < 500;
}

void edgeSafe(){
  lineSensor = 0;
  bitWrite(lineSensor, 0, edgeDetect(0));
  bitWrite(lineSensor, 1, edgeDetect(1));

  switch (lineSensor){
    case 0b0000:
      goForward();
    case 0b0011:
    case 0b0001:
      turnRight();
      goForward();
    break;
    case 0b0010:
      turnLeft();
      goForward();
    break;
  }
}
//==================== End of RangeFinder ====================
//==================== Start of Main Program ====================
void setup()
{
  //Initialize communication
  Serial.begin(9600);
  Wire.begin();
  
  //XSHUT pin
  XShut(ShutPin1);
  XShut(ShutPin2);
  XShut(ShutPin3);
  
  //Set address
  initSensor(ShutPin1, sensor1, 0x31);
  initSensor(ShutPin2, sensor2, 0x32);
  initSensor(ShutPin3, sensor3, 0x33);

  //wait for PushButton
  initMotor();
  startWait();
}

void loop()
{
  edgeSafe();
  scanSensor();
}


