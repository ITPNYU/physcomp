const int stepPin = 2;
const int dirPin = 3;
const int stepsPerRevolution = 512;
bool direction = HIGH;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // motor  direction:
  digitalWrite(dirPin, direction);
  // move one revolution :
  for (int step = 0; step < stepsPerRevolution; step++) {
    // step the motor one step:
    digitalWrite(stepPin, HIGH);
    delay(1);
    digitalWrite(stepPin, LOW);
    delay(1);
  }
  // wait half a second:
  delay(500);
  // change direction:
  direction = !direction;
}
