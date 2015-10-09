const int buttonPin = 2;     // pin that the button's connected to
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  int buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, and it's now HIGH
    if (buttonState == HIGH) {
      Serial.println(buttonState);    // print it
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
}









