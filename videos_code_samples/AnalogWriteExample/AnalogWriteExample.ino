/*
  This code sample goes with the video https://vimeo.com/93554355
  created 2014
  by Tom Igoe
*/
void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  // get an analog reading:
  int onTime = analogRead(0);
  // use dedicated PWM to control the dimming of the LED:
  analogWrite(9, onTime/4);
}
