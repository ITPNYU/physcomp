/*
  Serial input example. Reads one byte in from the serial port
  and uses that value to set the analogWrite on one of the
  PWM output pins.

*/

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // set pin 6 as an output:
  pinMode(6, OUTPUT);

}

void loop() {
  // if there is any serial data available:
  if (Serial.available()) {
    // read the first serial byte available into a variable:
    int inputValue = Serial.read();
    // set the PWM output of pin 6 with the variable:
    analogWrite(6, inputValue);
  }
}
