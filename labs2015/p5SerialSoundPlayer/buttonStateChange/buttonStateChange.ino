int lastButtonState = LOW;    // previous state of the pushbutton
int buttonPressCount = 0;     // number of times the button's been pushed
void setup() {
  pinMode(2, INPUT);     // make pin 2 an input
  pinMode(3, OUTPUT);    // make pin 3 an output
  Serial.begin(9600);    // initialize serial communications
}

void loop() {
  char incoming = Serial.read();  // read incoming bytes
  if (incoming == 'H') {          // if you get H
    digitalWrite(3, HIGH);        // turn on the LED
  }
  if (incoming == 'L') {          // if you get L
    digitalWrite(3, LOW);         // turn off the LED
  }

  int currentButtonState = digitalRead(2);      // read the pushbutton
  if (currentButtonState != lastButtonState) {  // if the button has changed
    if (currentButtonState == HIGH) {           // and it's HIGH
      buttonPressCount++;                       // increment buttonPressCount
      Serial.print('H');                      // send an H
      //Serial.println(buttonPressCount);       // send buttonPressCount
    }
    lastButtonState = currentButtonState;       // save the current state for next time
  }
}
