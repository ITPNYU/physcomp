/*
  APDS9960 - Color Sensor
  Uses the Sparkfun_APDS9960 library

  This example reads color data from  an APDS9960 sensor
  and prints it to the Serial Monitor.

  Color values are red, green, blue, clear (or ambient light)

  Works with Sparkfun and Adafruit APDS9960 breakout boards

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
  if ( apds.enableLightSensor(false) ) {
    Serial.println("Color sensor is working");
  } else {
    Serial.println("Color function not responding.");
    // stop the sketch:
    while (true);
  }
}

void loop() {
  // red, green, blue, clear channels:
  uint16_t r, g, b, c = 0;

  // read the color
  apds.readRedLight(r);
  apds.readGreenLight(g);
  apds.readBlueLight(b);
  apds.readAmbientLight(c);

  // print the values
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.print(b);
  Serial.print(",");
  Serial.println(c);
}
