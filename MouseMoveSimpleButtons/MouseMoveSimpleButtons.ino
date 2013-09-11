
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
int lastButton1State = LOW;
boolean mouseIsActive = false;

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
  // read the pushbutton:
  int button1State = digitalRead(2);
  int button2State = digitalRead(3);
  int button3State = digitalRead(4);
  int button4State = digitalRead(5);
  int button5State = digitalRead(6);

  // if it's changed and it's high, toggle the mouse state:
  if (button1State != lastButton1State) {
    if (button1State == HIGH) {
      mouseIsActive = !mouseIsActive;
      Serial.println("Button 1");
      Serial.println(mouseIsActive);
    }
  }
  // save switch state for next comparison:
  lastButton1State = button1State;


// if the mouse is active, and any button is pressed,
// move the mouse in the corresponding direction:
  if(mouseIsActive) {
    if (button2State == HIGH) {
      Mouse.move(2, 0, 0);
    } 
    if (button3State == HIGH) {
      Mouse.move(-2, 0, 0);
    } 
    if (button4State == HIGH) {
      Mouse.move(0, 2, 0);
    } 
    if (button5State == HIGH) {
      Mouse.move(0, -2, 0);
    } 
  }
}

