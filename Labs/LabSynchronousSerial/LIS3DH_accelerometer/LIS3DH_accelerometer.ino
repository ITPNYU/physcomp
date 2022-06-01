/*
  Accelerometer

  This example reads an LIS3DH accelerometer using I2C
  Uses Sparkfun's LIS3DH library:
  https://github.com/sparkfun/SparkFun_LIS3DH_Arduino_Library

  The circuit:
   - LIS3DH accelerometer attached to SDA and SCL

  Note: to use Adafruit's breakout board with Sparkfun's library,
  you must connect SDO to +V.

  created 27 Nov. 2018
  by Tom Igoe
*/

#include "SparkFunLIS3DH.h"
#include "Wire.h"

LIS3DH accelerometer;

void setup() {
  Serial.begin(9600);
  accelerometer.begin();
}

void loop() {
  // read sensors:
  int xReading = accelerometer.readRawAccelX();
  int yReading = accelerometer.readRawAccelY();
  int zReading = accelerometer.readRawAccelZ();
  // print them out:
  Serial.print(xReading);
  Serial.print(",");
  Serial.print(yReading);
  Serial.print(",");
  Serial.println(zReading);
}
