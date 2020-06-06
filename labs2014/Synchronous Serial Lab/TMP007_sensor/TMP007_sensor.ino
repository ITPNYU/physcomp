/*
  TMP007 test sketch
  This is a basically the same sketch as the TMP007 example from Adafruit.
  Some names have been changed for readability.

*/
#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_TMP007.h>

Adafruit_TMP007 tmp007; // instance of the sensor library

void setup() {
  Serial.begin(9600);
  boolean sensorInitialized = tmp007.begin(); // initialize the sensor

  while (!sensorInitialized) {
    // Do nothing until sensor responds
    Serial.println("Sensor is not responding");
  }
}

void loop() {
  if (millis() % 4000 < 2) { // if 4 seconds have passed
    float objectTemp = tmp007.readObjTempC(); // read object temperature
    float chipTemp = tmp007.readDieTempC(); // read chip temperature

    // print the results:
    Serial.print("Chip temperature: ");
    Serial.print(chipTemp);
    Serial.print(" deg. C. \t Object temperature: ");
    Serial.print(objectTemp);
    Serial.println(" deg. C");
  }
}
