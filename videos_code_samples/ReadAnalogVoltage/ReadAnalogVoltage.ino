/*
  This code sample goes with the video https://vimeo.com/90534361
*/

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // read the analog input:
  int sensorReading = analogRead(A0);
  // Convert the ADC reading to voltage:
  float voltage = sensorReading * (5.0 / 1023.0);
  // map the sensor's input range (0 - 874) to a range from 0-3:
  int lightness = map(0, 874, 0, 3);
  
  // print out the value you read:
  Serial.print(lightness);
  Serial.print("\t");
  Serial.print(voltage);
  Serial.print("\t");
  Serial.println(sensorReading);
}
