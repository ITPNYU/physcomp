/*
  Serial out binary
  Uses a call-and-response approach to send a binary
  two-byte value from the serial port.

  created 2 Nov 2016
  by Tom Igoe
*/

void setup() {
  Serial.begin(9600);
}

void loop() {
  // wait for a byte of data from the other side:
  if (Serial.available() > 0) {
    // read the byte to clear the input buffer:
    int inByte = Serial.read();
    // read the sensor:
    int sensor = analogRead(A0);
    // send the high byte of the sensor reading:
    Serial.write(highByte(sensor));
    // send the low byte of the sensor reading:
    Serial.write(lowByte(sensor));
  }
}
