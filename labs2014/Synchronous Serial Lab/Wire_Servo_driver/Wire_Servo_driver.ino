#include <Servo.h>
#include <Wire.h>

const int myAddress = 1;
Servo leftServo;
Servo rightServo;
int leftAngle;
int rightAngle;


void setup() {
  Wire.begin(myAddress);
  Wire.onReceive(readIncoming);
  Wire.onRequest(sendOutgoing);

  leftServo.attach(8);
  rightServo.attach(9);
}

void loop() {
  if (millis() % 20 < 2) {
    leftServo.write(leftAngle);
    rightServo.write(rightAngle);
  }
}

void readIncoming(int byteCount) {
  while (Wire.available() > 0) {
    int servoNumber = Wire.read();
    int angle = Wire.read();
    if (servoNumber == 1) {
      leftAngle = angle;
    } else {
      rightAngle = angle;
    }
  }
}

void sendOutgoing() {
  Wire.write(myAddress);
}
