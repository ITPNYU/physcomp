/*
  APDS9960 - Color Sensor
  Uses the Adafruit_APDS9960 library

  This example reads color data from  an APDS9960 sensor
  and prints it to the Serial Monitor.

  Color values are red, green, blue, clear (or ambient light)

  Works with Nano 33 BLE Sense, and Sparkfun and Adafruit APDS9960 breakout boards

  The circuit:
  - Arduino Nano 33 BLE Sense
  or
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
  if ( !apds.begin()) {
    Serial.println("APDS9960 sensor not working. Check your wiring.");
    // stop the sketch:
    while (true);
  }
  apds.enableColor();
}

void loop() {
  // red, green, blue, clear channels:
  uint16_t r, g, b, c = 0;

  if (apds.colorDataReady()) {
    apds.getColorData(&r, &g, &b, &c);

    // print the values
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.print(b);
    Serial.print(",");
    Serial.println(c);
  }
}
