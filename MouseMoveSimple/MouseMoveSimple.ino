/*
  Simple mouse control from analog inputs
  
  This sketch uses two analog inputs, A0, and A1, to control the 
  horizontal axis of the mouse. It only runs on a Leonardo, Micro, or Yun.
    
  A pushbutton on digital pin 2 controls whether or not
  the Arduino takes control of the mouse.
  
    When there's a significant difference between the two analog sensors
  (i.e. more than 100), the mouse moves left or right, 
  depending on which sensor is greater.

  
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
  delay(1);
  int sensor2 = analogRead(A1);

  // print their values. Remove this when you have things working:
  Serial.print(sensor1);
  Serial.print("  ");
  Serial.println(sensor2); 

  // if there's a significant difference to the right:
  if (sensor1 > sensor2 + 100){
    //  Serial.println("L"); 
    if (mouseIsActive == true) {
      Mouse.move(-1, 0, 0);
    }
  } 

  // if there's a significant difference to the left:
  else if (sensor2 > sensor1 + 100) {
    // Serial.println("R");
    if (mouseIsActive == true) {
      Mouse.move(1, 0, 0);
    }
  }
}
