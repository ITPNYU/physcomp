/*
  Button state change long press example

  Shows how to detect a tap on a button, a short press, or a long press.

  circuit:
  - pushbutton with 10K pulldown resistor on pin 3. Button is connected to voltage
 
  created 1 Dec 2020
  updated 5 Aug 2021
  by Tom Igoe
*/
// the input pin:
int buttonPin = 3;

// the length of the presses in ms:
int longPress = 750;
int shortPress = 250;
// variable for how long the user actually presses:
long pressTime = 0;

// previous state of the button:
int lastButtonState = LOW;

void setup() {
  // initialize serial and I/O pin:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the button:
  int buttonState = digitalRead(buttonPin);

  // if the button has changed:
  if (buttonState != lastButtonState) {
    // if the button is pressed, start a timer:
    if (buttonState == HIGH) {
      pressTime = millis();
    }
    // if it's released, stop the timer:
    if (buttonState == LOW) {
      long holdTime = millis() - pressTime;
      // take action for long press, short press, or tap:
      if (holdTime > longPress) {
        Serial.println("long press");
      } else if (holdTime > shortPress) {
        Serial.println("short press");
      } else {
        Serial.println("Tap");
      }
    }
  }
  // save button state for next time:
  lastButtonState = buttonState;
}
