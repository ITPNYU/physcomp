/*
  Keyboard seven pushbuttons to control Zoom
  Reads an array of pushbuttons. If any one has just been pressed,
  sends a keystroke combo.
  Full list of Zoom commands:
  https://support.zoom.us/hc/en-us/articles/205683899-Hot-Keys-and-Keyboard-Shortcuts-for-Zoom

  Works on SAMD boards (MKR series, Nano 33 IoT),
  Leonardo, Due, and other USB-native boards

  created 27 July 2020
  by Tom Igoe

*/

#include <Keyboard.h>
// debounce delay for pushbutton:
const int debounceDelay = 4;
int buttonCount = 7;
//  pushbuttons are on these pins:
int buttonPin[] = {2, 3, 4, 5, 6, 7, 8};
// previous states of the buttons:
int lastButtonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

// platform: 0 for MacOS, 1 for Windows, 2 for Linux:
int platform = 0;

void setup() {
  // initialize Keyboard:
  Keyboard.begin();
  // set button input modes:
  for (int b = 0; b < buttonCount; b++) {
    pinMode(buttonPin[b], INPUT_PULLUP);
  }
}

void loop() {
  // iterate over the button list:
  for (int b = 0; b < buttonCount; b++) {
    // read this button:
    int buttonState = digitalRead(buttonPin[b]);
    // if it has changed:
    if (buttonState != lastButtonState[b]) {
      // wait until button state stabilizes:
      delay(debounceDelay);
      // if it's low:
      if (buttonState == LOW) {
        // send keystroke:
        sendKeyCombination(buttonPin[b]);
      }
      // save current state for next time:
      lastButtonState[b] = buttonState;
    }
  }
}

void sendKeyCombination(int thisButton) {
  // command-shift for most of these on MacOS:
  if (platform == 0) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_GUI);
  }
  // alt for most of these on Windows or Linux:
  if (platform == 1 || platform == 2) {
    Keyboard.press(KEY_LEFT_ALT);
  }

  switch (thisButton) {
    case 2: // A:  Mute/unmute audio
      Keyboard.press('A');
      break;
    case 3: // V: Start/stop video
      Keyboard.press('V');
      break;
    case 4: // N: Switch camera
      Keyboard.press('N');
      break;
    case 5: // S: Start/stop screen share
      if (platform == 1) {
        // Ctrl+Alt+Shift: Move focus to Zoom's meeting controls
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_SHIFT);
        delay(30);
        Keyboard.release(KEY_LEFT_CTRL);
      }
      Keyboard.press('S');
      break;
    case 6: // T: Pause or resume screen share
      Keyboard.press('T');
      break;
    case 7: // P: Pause or resume recording
      Keyboard.press('P');
      break;
    case 8: // Ctrl+\: Toggle the "Always Show meeting controls"
      if (platform == 0) {
        Keyboard.releaseAll();
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('\\');
      }
      if (platform == 1 || platform == 2) {
        Keyboard.release(KEY_LEFT_ALT);
      }
      break;
  }
  delay(30);
  Keyboard.releaseAll();
}
