/*
  APDS9960 - Gesture Sensor
  Uses the Sparkfun_APDS9960 library
  
  This example reads gesture data from  an APDS9960 sensor
  and prints  detected gestures to the Serial Monitor.

  Gesture directions are as follows: UP (1), DOWN (1), LEFT (2), RIGHT (3)
  NEAR(4), FAR (5)
  Works at about 10cm or less.

  The circuit:
  - Any Arduino and APDS9960 breakout board, with:
    - APDS9960 SDA connected to Arduino SDA (A4)
    - APDS9960 SCL connected to Arduino SCL (A5)
*/


#include <SparkFun_APDS9960.h>
SparkFun_APDS9960 apds = SparkFun_APDS9960();

void setup() {
  Serial.begin(9600);
  // wait for Serial Monitor to open:
  while (!Serial);
  // if the sensor doesn't initialize, let the user know:
  if ( !apds.init()) {
    Serial.println("APDS9960 sensor not working. Check your wiring.");
    // stop the sketch:
    while (true);
  }

  apds.enableGestureSensor(true);
  Serial.println("Sensor is working");
}
void loop() {
  // if the sensor has a reading:
  if (apds.isGestureAvailable()) {
    // and a gesture was detected:
    uint8_t gesture = apds.readGesture();
    // gestures have numeric values and constant names:
    switch (gesture) {
      case DIR_UP:   // 0
        Serial.println("UP");
        break;
      case DIR_DOWN: // 1
        Serial.println("DOWN");
        break;
      case DIR_LEFT: // 2
        Serial.println("LEFT");
        break;
      case DIR_RIGHT: // 3
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
    }
  }
}
