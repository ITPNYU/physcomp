void setup() {
  Serial.begin(9600);     // initialize serial communications
  Serial.setTimeout(10);  // set the timeout for parseInt
}

void loop() {
  if (Serial.available() > 0) {     // if there's serial data available
    int inByte = Serial.parseInt(); // read it
    if (inByte > 0) {
      Serial.write(inByte);         // send it back out as raw binary data
      analogWrite(5, inByte);       // use it to set the LED brightness
      // if you're using a speaker instead of an LED, uncomment line below  and comment out the previous line:
      //  tone(5, inByte*10);     // play tone on pin 5
    }
  }
}
