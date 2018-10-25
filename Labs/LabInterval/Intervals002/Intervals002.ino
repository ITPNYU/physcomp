/*
  A demonstration of how to manage output tasks on different time intervals
  using the millis() function.
  This version uses arrays to group variables with similar functions

  created 25 Oct 2018
  by Tom Igoe
*/

// set pin numbers for three buttons, and three LEDs.
// the LEDs should be om PWM pins.
const int buttonPin[] = {2, 3, 4};
const int ledPin[] = {9, 10, 11};

// create variables for LED brightnesses:
int ledBrightness[3];

// create variables for LED fade timestamps:
long lastFade[3];

// create variables for LED fade intervals:
long interval[] = {1000, 3000, 5000};

void setup() {
  // set the input and output pin modes:
  for (int p = 0; p < 3; p++) {
    pinMode(buttonPin[p], INPUT);
    pinMode(ledPin[p], OUTPUT);
  }
}

void loop() {
  // make a local variable for the button states:
  int buttonState[3];

  // iterate over all three button/LED combos:
  for (int p = 0; p < 3; p++) {
    // read the pushbuttons:
    buttonState[p] = digitalRead(buttonPin[p]);

    // if any button is pressed,
    // bump the corresponding LED brightness to full:
    if (buttonState[p] == HIGH) {
      ledBrightness[p] = 255;
    }

    // get the current time in millis:
    long now = millis();
    
    // fade the LEDs at three separate rates:
    // if the interval between fade steps has passed:
    if (now - lastFade[p] > interval[p]) {
      // if brightness > 0, decrement it by one:
      ledBrightness[p] = max(ledBrightness[p]--, 0);
      analogWrite(ledPin[p], ledBrightness[p]);
      // save the current time for next interval comparison:
      lastFade[p] = now;
    }
  }
}
