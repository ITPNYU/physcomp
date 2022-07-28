const int stepPin = 2;
const int dirPin = 3;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // motor  direction: 
  digitalWrite(dirPin, HIGH);
  // step the motor one step:
  digitalWrite(stepPin, HIGH);
  delay(3);
  digitalWrite(stepPin, LOW);
  // wait half a second:
  delay(500);
}