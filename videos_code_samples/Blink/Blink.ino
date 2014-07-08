/*
  This code sample goes with the video https://vimeo.com/86534049
  created 2014
  by Tom Igoe
*/

void setup() {
  // tell the microcontroller what pin is an output:
  pinMode(2, OUTPUT);

}

void loop() {
  digitalWrite(2, HIGH);  // send 5V to the pin
  delay(1000);    // do nothing for half a second
  digitalWrite(2, LOW);   // send 0V to the pin
  delay(1000);    // do nothing again
}
