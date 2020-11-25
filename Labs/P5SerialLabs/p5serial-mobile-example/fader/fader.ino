/*
  Reads serial byte in, uses it to set two PWM channels, a warm white LED
  and a cool white LED.

*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // if there is incoming data:
  if (Serial.available() > 0) {
    // read it:
    int intensity = Serial.read();
    // send it back as a string:
    Serial.println(inData);
    // control the cool white LEDs:
    analogWrite(5, intensity);
    // control the warm white LEDs:
    analogWrite(6, 255 - intensity);
  }
}
