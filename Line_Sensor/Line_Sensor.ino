// initialize variables
int ledPin = 11, sensor = 0, brightness = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  brightness = analogRead(sensor);
  //analogWrite(ledPin, brightness/4);
  Serial.println(brightness);
}
