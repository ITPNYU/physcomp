/*
  APDS9960 - Color Sensor

  This example reads Color data from the on-board APDS9960 sensor of the
  Nano 33 BLE Sense and prints the color RGB (red, green, blue) values
  to the Serial Monitor once a second.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
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
  // red, green, blue, clear channels:
  int r, g, b, c;

  // if the sensor has a reading:
  if (APDS.colorAvailable()) {

    // read the color
    APDS.readColor(r, g, b, c);

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
