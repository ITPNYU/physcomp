/*
  AnalogReadSerial with handshaking

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Waits for incoming serial response before it sends again
 
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while (!Serial.available()) { // until the server responds,
    Serial.println("hello");    // send a hello message
    delay(500);                 // every half second
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // if there are incoming bytes:
  if (Serial.available()) {
    // read incoming byte:
    int input = Serial.read();
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorValue);
    delay(1);        // delay in between reads for stability
  }
}

