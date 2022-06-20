#include <EncoderStepCounter.h>

const int pin1 = 2;
const int pin2 = 3;

// Create encoder instance:
EncoderStepCounter encoder(pin1, pin2);

// encoder previous position:
int oldPosition = 0;

const int buttonPin = 4;    // pushbutton pin
int lastButtonState = LOW;  // last button state
int debounceDelay = 5;      // debounce time for the button in ms


void setup() {
  Serial.begin(9600);
  // Initialize encoder
  encoder.begin();
  // Initialize interrupts
  attachInterrupt(digitalPinToInterrupt(pin1), interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin2), interrupt, CHANGE);
  // set the button pin as an input_pullup:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // if you're not using interrupts, you need this in the loop:
  encoder.tick();

  // read encoder position:
  int position = encoder.getPosition();
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  //  // if the button has changed:
  if (buttonState != lastButtonState) {
    // debounce the button:
    delay(debounceDelay);
    // if button is pressed:
    if (buttonState == LOW) {
      Serial.print("you pressed on position: ");
      Serial.println(position);
    }
  }
  // save current button state for next time through the loop:
  lastButtonState = buttonState;

  // reset the encoder after 24 steps:
  if (position % 24 == 0) {
    encoder.reset();
    position = encoder.getPosition();
  }
  // if there's been a change, print it:
  if (position != oldPosition) {
    Serial.println(position);
    oldPosition = position;
  }
}

// Call tick on every change interrupt
void interrupt() {
  encoder.tick();
}