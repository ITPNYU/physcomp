/*
  This code sample goes with the video https://vimeo.com/XXXX
  created 2014
  by Tom Igoe
*/
void setup() {
  Serial.begin(9600);   
}

void loop() {
 int sensor = analogRead(A0);
 Serial.write(sensor/4);
 delay(10);
}
