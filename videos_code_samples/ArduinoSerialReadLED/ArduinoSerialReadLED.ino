/*
  This code sample goes with the video https://vimeo.com/97520383
  created 2014
  modified 30 Aug 2015
  by Tom Igoe
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char input = Serial.read();
    // use the value of the incoming byte to control the LED's brightness:
    analogWrite(11, input);
  }
}
