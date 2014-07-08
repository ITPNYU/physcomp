/*
  This code sample goes with the video https://vimeo.com/93608912
  created 2014
  by Tom Igoe
*/

#include <Servo.h>    // add the servo library
Servo myServo;        // make a local instance of the servo library

void setup() {
  // attach the servo to pin 9:
  myServo.attach(9);
}

void loop() {
  // get an analog reading:
  int sensor = analogRead(0);
  // map the sensor output to a range from 0 - 180:
  int angle = map(sensor, 0, 1023, 0, 180);
  // wait 20ms before the next loop.
  // this uses the modulo operator (%)
  // that gives you the remainder of the division of the two numbers.
  // e.g. 23 % 20 = 3, because 23 /20 has a remainder of 1:
  if (millis() % 20 < 2) {
    myServo.write(angle);
  }
}
