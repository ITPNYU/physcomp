/*
  Accelerometer read

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
*/
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
//  sensor range is 490 to 540. Map it to 440 to 880 for pitch:
  int pitch = map(sensorValue, 490, 540, 440, 880);
  // print out the value you read:
  Serial.println(pitch);
   // delay to allow Accelerometer to stabilize
  delay(20);       
}
