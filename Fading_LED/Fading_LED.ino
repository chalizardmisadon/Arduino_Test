int ledPin = 13, period = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  delayMicroseconds(period);
  digitalWrite(ledPin, LOW);
  delayMicroseconds(1000-period);
  if (period > 999) period = 0;
  else period += 1;

}
