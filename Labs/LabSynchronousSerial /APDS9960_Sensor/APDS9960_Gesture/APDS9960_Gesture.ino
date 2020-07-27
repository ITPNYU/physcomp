/*
  APDS9960 - Gesture Sensor

  This example reads gesture data from  an APDS9960 sensor
  and prints  detected gestures to the Serial Monitor.

  Gesture directions are as follows: UP (1), DOWN (1), LEFT (2), RIGHT (3)
  Works at about 10cm or less.

  Works with Nano 33 BLE Sense, and Sparkfun and Adafruit APDS9960 breakout boards

  The circuit:
  - Arduino Nano 33 BLE Sense
  or
  - Any Arduino and APDS9960 breakout board, with:
    - APDS9960 SDA connected to Arduino SDA (A4)
    - APDS9960 SCL connected to Arduino SCL (A5)
*/

#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  // wait for Serial Monitor to open:
  while (!Serial);
  // if the sensor doesn't initialize, let the user know:
  if (!APDS.begin()) {
    Serial.println("APDS9960 sensor not working. Check your wiring.");
    // stop the sketch:
    while (true);
  }

  // gesture sensitivity range: 1 - 100. Default: 80
  // higher means more sensitivity, more errors.
  // lower means less sensitivity, less errors.
  APDS.setGestureSensitivity(80);
  Serial.println("Sensor is working");
}
void loop() {
  // if the sensor has a reading:
  if (APDS.gestureAvailable()) {
    // and a gesture was detected:
    int gesture = APDS.readGesture();
    Serial.println(gesture);
    // gestures have numeric values and constant names:
    switch (gesture) {
      case GESTURE_UP:   // 0
        Serial.println("UP");
        break;
      case GESTURE_DOWN: // 1
        Serial.println("DOWN");
        break;
      case GESTURE_LEFT: // 2
        Serial.println("LEFT");
        break;
      case GESTURE_RIGHT: // 3
        Serial.println("RIGHT");
        break;
    }
  }
}
