void setup() {
 Serial.begin(9600); // initialize serial communications
}
 
void loop() {
 int potentiometer = analogRead(A0);                  // read the input pin
 int mappedPot = map(potentiometer, 0, 1023, 0, 255); // remap the pot value to fit in 1 byte
 Serial.write(mappedPot);                             // print it out the serial port
 delay(1);                                            // slight delay to stabilize the ADC
}
