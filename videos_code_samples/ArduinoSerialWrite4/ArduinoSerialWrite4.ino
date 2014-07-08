/*
  This code sample goes with the video https://vimeo.com/XXXX
  created 2014
  by Tom Igoe
*/
void setup() {
  Serial.begin(9600);
  Serial.println("0,0");  
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int sensor = analogRead(A0);
    Serial.print(sensor);
    Serial.print(",");
    delay(1);

    int sensor2 = analogRead(A1);
    Serial.println(sensor2);
    //delay(10);
  }
}
