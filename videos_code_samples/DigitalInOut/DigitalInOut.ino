/*
  This code sample goes with the video https://vimeo.com/86548673
  created 2014
  by Tom Igoe
*/
void setup() {
  // configure the input and output pins:
  pinMode(2, OUTPUT);  // the LED
  pinMode(3, INPUT);   // the switch (pushbutton)

}

void loop() {
  // read the state of the pushbutton:
  int buttonState = digitalRead(3);
  // write to the LED depending on the state of the button
  if (buttonState == HIGH) {
    // turn the LED off
    digitalWrite(2, LOW);
  } else {
    // turn the LED on
    digitalWrite(2, HIGH);
  }
}
