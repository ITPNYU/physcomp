const int switchPin = 6;    // switch input
const int motor1Pin = 4;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 5;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 3;    // H-bridge enable pin

void setup() {
  // set the switch as an input:
  pinMode(switchPin, INPUT);

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin, HIGH);
}

void loop() {
  // if the switch is high, motor will turn on one direction:
  if (digitalRead(switchPin) == HIGH) {
    // set leg 1 of the H-bridge low:
    digitalWrite(motor1Pin, LOW);
    // set leg 2 of the H-bridge high:
    digitalWrite(motor2Pin, HIGH);
  }
  // if the switch is low, motor will turn in the other direction:
  else {
    // set leg 1 of the H-bridge high:
    digitalWrite(motor1Pin, HIGH);
    // set leg 2 of the H-bridge low:
    digitalWrite(motor2Pin, LOW);
  }
}
