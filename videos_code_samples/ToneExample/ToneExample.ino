/*
  This code sample goes with the video https://vimeo.com/93610177
  created 2014
  by Tom Igoe
*/
void setup() {

}

void loop() {
  // get an analog reading:
  int sensor = analogRead(0);
  // map the sensor output to a range from 100 - 880:
  int frequency = map(sensor, 0, 1023, 100, 880);
  // play a tone on the speaker on pin 9:
  tone(9, frequency);
}
