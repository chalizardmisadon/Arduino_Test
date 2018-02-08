int trig = 11, echo = 12, data, distance = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

}

void loop(){
  // put your main code here, to run repeatedly:
  delayMicroseconds(2); // delay to prevent ultrasensor overheat
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // read signal
  data = pulseIn(echo, HIGH, 5800);
  distance = data / 58;

  Serial.println(distance);


  
}
