/*
   Keyboard control from pushbuttons

   Sends keystrokes from pushbutton values. Also shows how to use shift key
   as an example of a modifier key

   created 13 Oct 2018
   by Tom Igoe
*/

#include <Keyboard.h>
// Global variables:
int buttonState[5];      // states of the buttons
int lastButtonState[5];  // previous states of the buttons
// whether or not the Arduino is controlling the keyboard:
bool keyboardIsActive = false;
int repeatRate = 50;    // key repeat rate, in milliseconds

// keys to be pressed by the keyboard buttons:
int key[] = {KEY_LEFT_SHIFT, 'a', 's', 'd'};

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // set the pins as INPUTs:
  for (int b = 2; b < 7; b++) {
    pinMode(b, INPUT);
  }
  // make the LED pin an output:
  pinMode(13, OUTPUT);
}

void loop() {
  // iterate over the buttons:
  for (int b = 0; b < 5; b++) {
    // pin number = array index number + 2:
    buttonState[b] = digitalRead(b + 2);
    // see if the button has changed:
    if (buttonState[b] != lastButtonState[b]) {
      Serial.print("button ");
      Serial.print(b);
      if (buttonState[b] == HIGH)
      { // pressed
        buttonAction(b, 0);
        //Serial.println(" pressed");
      } else { // released
        buttonAction(b, 1);
        //Serial.println(" released");
      }
    } else {
      if (buttonState[b] == HIGH) {
        buttonAction(b, 2);
        //Serial.println(" still pressed");
      }
    }
    // save button's current state as previous state for next loop:
    lastButtonState[b] = buttonState[b];
  }
}


void buttonAction(int buttonNumber, int buttonState) {
  // the keyboard state change button
  if (buttonNumber == 0) {
    // on press, toggle keyboardIsActive
    if (buttonState == HIGH) {
      keyboardIsActive = !keyboardIsActive;
      // activate the keyboard:
      if (keyboardIsActive) {
        Keyboard.begin();
      } else {
        Keyboard.end();
      }
      // change the LED to reflect the keyboard state:
      digitalWrite(13, keyboardIsActive);

      /*
      // an alternative to the LED indicator is a buzzer
      // indicator on the same pin. The following will buzz
      // once when you activate the keyboard, twice, when you
      // deactivate:

      keyboardIsActive = !keyboardIsActive;
      // activate the keyboard:
      if (keyboardIsActive) {
        Keyboard.begin();
        //buzz once for active:
        digitalWrite(13, HIGH);
        delay(300);
        digitalWrite(13, LOW);
      } else {
        Keyboard.end();
        //buzz twice for inactive:
        digitalWrite(13, HIGH);
        delay(300);
        digitalWrite(13, LOW);
        delay(300);
        digitalWrite(13, HIGH);
        delay(300);
        digitalWrite(13, LOW);
        }
      */
    }
  }
  // the other three buttons:
  if (keyboardIsActive) {
    if (buttonNumber > 0 ) {
      if (buttonState == HIGH) {
        Keyboard.press(key[buttonNumber - 1]);
        Serial.println(" pressed");
      }
      if (buttonState == LOW) {
        Keyboard.release(key[buttonNumber - 1]);
        Serial.println(" released");
      }
    }
    // all the buttons other than the shift button and the keyboard state button:
    if (buttonNumber > 1) {
      if (buttonState == 2) { // pressed
        Keyboard.write(key[buttonNumber - 1]);
        Serial.println(" repeating");
        delay(repeatRate);
      }
    }
  }
}
