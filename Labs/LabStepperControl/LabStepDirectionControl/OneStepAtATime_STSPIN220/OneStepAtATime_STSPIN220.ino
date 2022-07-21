const int stepPin = 2;
const int dirPin = 3;

bool direction = HIGH;
void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // motor  direction:
  digitalWrite(dirPin, direction);
  // move ten steps:
  for (int step = 0; step < 10; step++) {
    // step the motor one step:
    digitalWrite(stepPin, HIGH);
    delay(1);
    digitalWrite(stepPin, LOW);
    // wait half a second:
    delay(500);
  }
  // change direction:
  direction = !direction;
}
