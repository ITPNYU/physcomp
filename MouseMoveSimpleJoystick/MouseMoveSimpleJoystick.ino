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

int lastButtonState = LOW;
int lastButton2State = LOW;

boolean mouseIsActive = false;

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
      mouseIsActive = !mouseIsActive;
    }
  }
  // save switch state for next comparison:
  lastButtonState = buttonState;




  // read the analog sensors:
  int sensor1 = analogRead(A0);
  delay(1);
  int sensor2 = analogRead(A1);

  int xAxis = (sensor1 / 100) - 5;
  int yAxis = (sensor2 / 100) - 5;
  // print their values. Remove this when you have things working:
  Serial.print(xAxis);
  Serial.print("  ");
  Serial.println(yAxis); 


  if (mouseIsActive == true) {
    Mouse.move(xAxis, yAxis, 0);

    // read the pushbutton:
    int button2State = digitalRead(3);

    // if it's changed and it's high, toggle the mouse state:
    if (button2State != lastButton2State) {
      if (button2State == LOW) {
        Mouse.press();
      } 
      else {
        Mouse.release(); 
      }
    }
    // save switch state for next comparison:
    lastButton2State = button2State;
  }



}












