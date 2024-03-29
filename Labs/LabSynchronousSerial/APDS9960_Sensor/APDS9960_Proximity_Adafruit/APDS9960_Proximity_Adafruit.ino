/*
  APDS9960 - Proximity Sensor
  Uses the Adafruit_APDS9960 library
  
  This example reads proximity data from  an APDS9960 sensor
  and prints  detected gestures to the Serial Monitor.

  Proximity values are 255 (near, around 4cm) - 0 (far, around 10cm)
  Works at about 10cm or less.

  Works with Sparkfun and Adafruit APDS9960 breakout boards

  The circuit:
  - Any Arduino and APDS9960 breakout board, with:
    - APDS9960 SDA connected to Arduino SDA (A4)
    - APDS9960 SCL connected to Arduino SCL (A5)
*/

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

void setup() {
  Serial.begin(9600);
  // wait for Serial Monitor to open:
  while (!Serial);
  // if the sensor doesn't initialize, let the user know:
  if (!apds.begin()) {
    Serial.println("APDS9960 sensor not working. Check your wiring.");
    // stop the sketch:
    while (true);
  }

  Serial.println("Sensor is working");
  //enable proximity mode
  apds.enableProximity(true);

}

void loop() {
  // read and print the proximity:
  int proximity = apds.readProximity();
  // note: Adafruit library uses 255 = near, 0 = far
  Serial.println(proximity);
}
