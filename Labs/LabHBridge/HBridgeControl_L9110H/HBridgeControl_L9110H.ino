const int switchPin = 2;  // pushbutton input
const int motor1Pin = 5;  // H-bridge leg 1 (pin 6, 1A)
const int motor2Pin = 6;  // H-bridge leg 2 (pin 7, 2A)

// speed of the motor (0-255):
int speed = 127;

void setup() {
  // set the pushbutton as an input:
  pinMode(switchPin, INPUT);

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
}

void loop() {
  // if the pushbutton is high, motor will turn on one direction:
  if (digitalRead(switchPin) == HIGH) {
    // set leg 1 of the H-bridge low:
    digitalWrite(motor1Pin, LOW);
    // set leg 2 of the H-bridge high:
    analogWrite(motor2Pin, speed);
  }
  // if the pushbutton is low, motor will turn in the other direction:
  else {
    // set leg 1 of the H-bridge high:
    digitalWrite(motor1Pin, speed);
    // set leg 2 of the H-bridge low:
    digitalWrite(motor2Pin, LOW);
  }
}