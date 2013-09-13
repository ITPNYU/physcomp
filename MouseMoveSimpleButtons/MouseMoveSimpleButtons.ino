
/*
  Simple mouse control from buttons
 
 This sketch uses four pushbuttons, on digital pins 3 through 6, to control the 
 horizontal axis of the mouse. It only runs on a Leonardo, Micro, or Yun.
 
 A pushbutton on digital pin 2 controls whether or not
 the Arduino takes control of the mouse.
 
 When mouse control is active, and any of the other four pushbuttons are pressed,
 the mouse moves in the direction assigned to that button.
 
 created 11 September 2013
 by Tom Igoe
 
 */
// Global variables:
int lastButtonState = LOW;        // state of the button last time you checked
boolean mouseIsActive = false;    // whether or not the Arduino is controlling the mouse

void setup() {
  // initialize mouse control:
  Mouse.begin();
  // initialize serial communication:
  Serial.begin(9600);
  // make pin 2 through 5 inputs:
  pinMode(2, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
}

void loop() {
  // read the first pushbutton:
  int buttonState = digitalRead(2);

  // if it's changed and it's high, toggle the mouse state:
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // if mouseIsActive is true, make it false;
      // if it's false, make it true:
      mouseIsActive = !mouseIsActive;
    }
  }
  // save button state for next comparison:
  lastButtonState = buttonState;


  // if the mouse is active, and any button is pressed,
  // move the mouse in the corresponding direction:
  if(mouseIsActive) {
    // read the other buttons:
    int button2State = digitalRead(3);
    int button3State = digitalRead(4);
    int button4State = digitalRead(5);
    int button5State = digitalRead(6);

    if (button2State == HIGH) {
      Mouse.move(2, 0, 0);      // move right
    } 
    if (button3State == HIGH) {
      Mouse.move(-2, 0, 0);     // move left
    } 
    if (button4State == HIGH) {
      Mouse.move(0, 2, 0);      // move down
    } 
    if (button5State == HIGH) {
      Mouse.move(0, -2, 0);      // move up
    } 
  }
}
