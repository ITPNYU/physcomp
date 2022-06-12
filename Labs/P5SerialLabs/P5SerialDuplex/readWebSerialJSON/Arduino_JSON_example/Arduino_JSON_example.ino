#include <Arduino_JSON.h>
// make a new JSONVar object called device:
JSONVar device;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // make a data item called x in the JSONVar object:
  device["x"] = analogRead(A0);
  delay(1);
  // make a data item called y in the JSONVar object:
  device["y"] = analogRead(A1);
  delay(1);
  // make a data item called z in the JSONVar object:
  device["z"] = analogRead(A2);
  // print out the JSONVar object:
  Serial.println(device);
}