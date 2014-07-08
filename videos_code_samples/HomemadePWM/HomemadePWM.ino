/*
  This code sample goes with the video https://vimeo.com/86548673
  created 2014
  by Tom Igoe
*/
void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  // get an analog reading:
  int onTime = analogRead(0);
  // turn the LED on:
  digitalWrite(9, HIGH);
  // delay for a fraction of a millisecond:
  delayMicroseconds(onTime);
  // turn the LED off:
  digitalWrite(9, LOW);
  // delay for the rest of the millisecond:
  delayMicroseconds(1023 - onTime);
}
