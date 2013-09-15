/*
  Simple mouse control from potentiometers
 
 This sketch uses two potentiometers, A0, and A1, to control the 
 horizontal axis of the mouse, and a digital one, Digital in 3,
 to control the mouse button.
 It only runs on a Leonardo, Micro, or Yun.
 
 A pushbutton on digital pin 2 controls whether or not
 the Arduino takes control of the mouse.
 
 When the potentiometers go below 512, the mouse moves up or left,
 and when they go above 512, the mouse moves down or right.
 
 When the pushbutton on digital pin 3 goes low, the mouse clicks. 
 When it goes high, the mouse releases.
 
 This works well with an Adafruit Analog Thumb Joystick.
 
 created 11 September 2013
 by Tom Igoe
 
 */

// Global varibles:
int lastButtonState = LOW;        // state of the button last time you checked
int lastButton2State = LOW;       // state of the other button last time you checked
boolean mouseIsActive = false;    // whether or not the Arduino is controlling the mouse

void setup() {
  // initialize mouse control:
  Mouse.begin();
  // initialize serial communication:
  Serial.begin(9600);
  // make pin 2 an input, using the built-in pullup resistor:
  pinMode(2, INPUT_PULLUP);
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
      Serial.print("Mouse control state" );
      Serial.println(mouseIsActive);
    }
  }
  // save button state for next comparison:
  lastButtonState = buttonState;


  // read the analog sensors:
  int sensor1 = analogRead(A0);
  delay(1);
  int sensor2 = analogRead(A1);

  int xAxis = map(sensor1, 0, 1023, -5, 5);
  int yAxis = map(sensor2, 0, 1023, -5, 5);
  // print their values. Remove this when you have things working:
  Serial.print(xAxis);
  Serial.print("  ");
  Serial.println(yAxis); 


  if (mouseIsActive == true) {
    Mouse.move(xAxis, yAxis, 0);

    // read the second pushbutton:
    int button2State = digitalRead(3);

    // if it's changed and it's high, toggle the mouse state:
    if (button2State != lastButton2State) {
      if (button2State == LOW) {
        Serial.println("mouse pressed");
        Mouse.press();
      } 
      else {
        Serial.println("mouse released");
        Mouse.release(); 
      }
    }
    // save second button state for next comparison:
    lastButton2State = button2State;
  }
}


