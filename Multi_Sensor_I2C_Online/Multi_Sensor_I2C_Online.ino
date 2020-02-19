//import library
#include <Wire.h>
#include <VL53L0X.h>

//variable declaration
VL53L0X sensor;
VL53L0X sensor2;

void setup()
{

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  delay(500);
  Wire.begin();


  Serial.begin (9600);

  pinMode(12, INPUT);
  delay(150);
  Serial.println("00");
  sensor.init(true);

  Serial.println("01");
  delay(100);
  sensor.setAddress((uint8_t)22);
  Serial.println("02");

  pinMode(13, INPUT);
  delay(150);
  sensor2.init(true);
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)25);
  Serial.println("04");

  Serial.println("addresses set");



}

void loop()
{
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;


  for (byte i = 1; i < 120; i++)
  {

    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
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
