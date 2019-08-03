/*
ADXL335 Accelerometer
 
 This example reads an ADXL335 accelerometer 
 and prints the analogRead value from each axis. 
 
 Circuit:
 * ADXL335 attached to pins A0 - A5 as follows:
 ** X axis: A2
 ** Y Axis: A1
 ** z Axis:  A0
 
 created 18 Aug 2013
 modified 3 Aug 2019
 by Tom Igoe
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  int xAxis = analogRead(A2);  // Xout pin of accelerometer
  Serial.print(xAxis);

  int yAxis = analogRead(A1);  // Yout pin of accelerometer
  Serial.print(",");
  Serial.print(yAxis);

  int zAxis = analogRead(A0);  // Zout pin of accelerometer
  Serial.print(",");
  Serial.println(zAxis);
}
