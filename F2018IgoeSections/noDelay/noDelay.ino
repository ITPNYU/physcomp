/*
  This sketch shows how to do three things on different intervals.
  An analog input is read every time through the loop.
  A servo is moved  every 20 milliseconds, based on the sensor reading
  A tone is generated every 2 seconds, based also on the sensor reading

  This is done with no delay() commands. Instead, you check the millis()
  and compare it to the last time you took each action (e.g. moving the servo
  or making the tone)

  created 3 Oct 2018
  by Tom Igoe
*/

#include <Servo.h>    // include the servo library

Servo myServo;        // make an instance of the servo library

int lastTone = 0;     // a timestamp variable for the tones
int lastMove = 0;     // a timestamp variable for the servo moves

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // attach the servo to pin 5:
  myServo.attach(5);
}

void loop() {
  // read the analog sensor:
  int sensor = analogRead(A0);
  // print its value out in the serial monitor:
  Serial.println(sensor);

  // map the sensor value to two other variables, pitch and angle:
  int pitch = map(sensor, 0, 1023, 100, 2000);
  int angle = map(sensor, 0, 1023, 0, 180);

  // if 20 milliseconds have passed, move the servo:
  if (millis() - lastMove > 20) {
    myServo.write(angle);
    // save the current time in the lastMove variable, for comparison next time:
    lastMove = millis();
  }

  // if 2000 millisecond have passed, make a tone and print "hello":
  if (millis() - lastTone > 2000) {
    Serial.println("hello");
    tone(6, pitch, 1000);
    // save the current time in the lastTone variable, for comparison next time:
    lastTone = millis();
  }
}
