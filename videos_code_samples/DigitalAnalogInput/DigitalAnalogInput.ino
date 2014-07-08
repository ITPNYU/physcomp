/*
  This code sample goes with the video https://vimeo.com/86551311
  created 2014
  by Tom Igoe
*/

void setup() {
  pinMode(8, INPUT); // set the switch's pin to be an input
  Serial.begin(9600);  // initialize serial communications
}

void loop() {
  int switchState = digitalRead(8); // read the switch
  int potState = analogRead(A0);    // read the potentiometer
  delay(1);              // pause to "rest" the ADC
  int photoCellState = analogRead(A1); // read photocell  

 // print the values out:
 Serial.print("switch: ");
 Serial.print(switchState);
 Serial.print("\t");    // print a tab
 Serial.print("potentiometer: ");
 Serial.print(potState);
 Serial.print("\t");    // print a tab
 Serial.print("photocell: ");
 Serial.println(photoCellState);  // end the line of printing
}
