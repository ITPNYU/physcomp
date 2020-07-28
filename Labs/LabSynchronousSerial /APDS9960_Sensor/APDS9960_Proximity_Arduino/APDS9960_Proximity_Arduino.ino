/*
  APDS9960 - Proximity Sensor
  Uses the Arduino_APDS9960 library

  This example reads proximity data from  an APDS9960 sensor
  and prints  detected gestures to the Serial Monitor.

  Proximity values are 0 (near, around 4cm) - 255 (far, around 10cm)
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

  Serial.println("Sensor is working");
}

void loop() {
  // If the sensor has a reading:
  if (APDS.proximityAvailable()) {
    // read and print the proximity:
    int proximity = APDS.readProximity();
    Serial.println(proximity);
  }
}
