int myGroupNumber = 2;     // change this to your group number
int lastReading = LOW;    // for the previous reading of the sensor

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(3, INPUT);
}

void loop() {
  // listen for physical input:
  int sensorReading = digitalRead(3);

  if (sensorReading != lastReading && sensorReading == HIGH) {
    // something important happened
    // (input changed from low to high),
    // so send (groupnumber+1) to serial out:
    Serial.println(myGroupNumber+1);
  } 
  // save the current reading for comparison
  // next time through the loop:
  lastReading = sensorReading;

}

