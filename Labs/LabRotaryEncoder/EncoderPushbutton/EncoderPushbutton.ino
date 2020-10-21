#include <Encoder.h>

// encoder on pins 2 and 3
Encoder myEncoder(2, 3);
// previous position of the encoder:
int lastPosition = 0;

// steps of the encoder's shaft:
int steps = 0;


const int buttonPin = 4;    // pushbutton pin
int lastButtonState = LOW;  // last button state
int debounceDelay = 5;       // debounce time for the button in ms

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  //  // if the button has changed:
  if (buttonState != lastButtonState) {
    // debounce the button:
    delay(debounceDelay);
    // if button is pressed:
    if (buttonState == LOW) {
      Serial.print("you pressed on ");
      Serial.println(steps);
    }
  }
  // save current button state for next time through the loop:
  lastButtonState = buttonState;

  // read the encoder:
  int newPosition = myEncoder.read();
  // compare current and last encoder state:
  int change = newPosition - lastPosition;
  // if it's changed by 4 or more (one detent step):
  if (abs(change) >= 4) {
    // get the direction (-1 or 1):
    int encoderDirection = (change / abs(change));
    steps += encoderDirection;
    // if you want to make the steps rollover, use this:
    if (steps < 0) steps = 23;
    steps = steps % 24;
    Serial.println(steps);

    // save encoder position for next time through loop:
    lastPosition = newPosition;
  }
}
