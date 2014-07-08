#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  int sensor = analogRead(A0);
  int angle = map(sensor, 0, 1023, 0, 180);
  if (millis() % 20 < 2) {
    myServo.write(angle);
  }
  int feedback = analogRead(A1);
  Serial.println(feedback);
}
