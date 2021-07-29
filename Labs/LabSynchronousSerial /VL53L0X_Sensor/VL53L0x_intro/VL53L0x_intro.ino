/*
  ST VL53L0X example using Adafruit library

  Reads the Vl53L0X sensor and reports the result in mm

  created 29 July 2021
  by Tom Igoe
*/

// include library
#include "Adafruit_VL53L0X.h"

// make an instance of the library:
Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

const int maxDistance  = 2000;

void setup() {
  // initialize serial, wait 3 seconds for
  // Serial Monitor to open:
  Serial.begin(9600);
  if (!Serial) delay(3000);

  // initialize sensor, stop if it fails:
  if (!sensor.begin()) {
    Serial.println("Sensor not responding. Check wiring.");
    while (true);
  }
  /* config can be:
    VL53L0X_SENSE_DEFAULT: about 500mm range
    VL53L0X_SENSE_LONG_RANGE: about 2000mm range
    VL53L0X_SENSE_HIGH_SPEED: about 500mm range
    VL53L0X_SENSE_HIGH_ACCURACY: about 400mm range, 1mm accuracy
  */
  sensor.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE);
  // set sensor to range continuously:
  sensor.startRangeContinuous();
}

void loop() {
  // if the reading is done:
  if (sensor.isRangeComplete()) {
    // read the result:
    int result = sensor.readRangeResult();
    // if it's with the max distance:
    if (result < maxDistance) {
      // print the result (distance in mm):
      Serial.println(result);

    }
  }
}
