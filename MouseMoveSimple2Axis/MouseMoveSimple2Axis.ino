/*
  Simple mouse control from analog inputs, 2-axis
 
 This sketch uses two analog inputs, A0, and A1, to control the 
 the mouse. It only runs on a Leonardo, Micro, or Yun.
 
 A pushbutton on digital pin 2 controls whether or not
 the Arduino takes control of the mouse.
 
 When teh analog sensors cross high or low thresholds, 
 the mouse moves left or right, or up or down.
 depending on which sensor is greater.
 
 created 11 September 2013
 by Tom Igoe
 
 */

// Global varibles:
int lastButtonState = LOW;        // state of the button last time you checked
boolean mouseIsActive = false;    // whether or not the Arduino is controlling the mouse

void setup() {
  // initialize mouse control:
  Mouse.begin();
  // initialize serial communication:
  Serial.begin(9600);
  // make pin 2 an input:
  pinMode(2, INPUT);
}

void loop() {
  // read the pushbutton:
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

  // read the analog sensors:
  int sensor1 = analogRead(A0);
  delay(1);            // short delay helps get good readings
  int sensor2 = analogRead(A1);

  // print their values. Remove this when you have things working:
  Serial.print(sensor1);
  Serial.print("  ");
  Serial.println(sensor2); 

  int xMove = 0;    // amount to move the mouse horizontally
  int yMove = 0;    // amount to move the mouse vertically

  // if sensor1 crosses a high threshold:
  if (sensor1 > 800){
    xMove = 2;
  } 
  // if sensor1 crosses a low threshold:
  if (sensor1 < 400) {
    xMove = -2; 
  }

  // if sensor2 crosses a high threshold:
  if (sensor2 > 800){
    yMove = 2;
  } 
  // if sensor2 crosses a low threshold:
  if (sensor2 < 400) {
    yMove = -2; 
  }
  //if the mouse is active, move it:
  if (mouseIsActive == true) {
    Mouse.move(xMove, yMove, 0);
  }
}
