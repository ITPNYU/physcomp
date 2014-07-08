// include the library code:
#include <LiquidCrystal.h>

int lastReading[8];         // set up an array of 8 buttons (1 per group)
int lastGroupNumber = 0;    // last group number received


// initialize the library with the numbers of the interface pins
// note: you're using the analog in pins as output pins here.
// you can do that:
LiquidCrystal lcd(12, 11, A0, A1, A2, A3);

void setup() {
  // initialize serial communiation:
  Serial.begin(9600);
  // open serial on the Leonardo/Micro TX/RX pins too:
  Serial1.begin(9600);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // pushbuttons are on pins 2 through 9.
  // make them inputs using the internal pullup resistors:
  for (int buttonNum = 2; buttonNum < 10; buttonNum++) {
    pinMode(buttonNum, INPUT_PULLUP);
  }
  lcd.setCursor(0,0);
  lcd.print("Hello XBee");
}

void loop() {
  // an array for storing current states of the buttons:
  int currentReading[8];
  int lastGroupNumber = 0;

  // loop over the buttons and check their current state
  // against their last state:
  for (int buttonNum = 2; buttonNum < 10; buttonNum++) {
    // array counts from 0 - 7, but buttons are 
    // numbered 2-9:
    currentReading[buttonNum-2] = digitalRead(buttonNum);
    // if the button you're checking has changed,
    // and it's HIGH, then send the last group number out serially:
    if (currentReading[buttonNum-2] != lastReading[buttonNum-2]) {
      delay(5);
      if (currentReading[buttonNum-2] == LOW) {
        // print to the Xbee via serial:
        Serial1.println(buttonNum-1);
        // print to the serial monitor via USB:
        Serial.println(buttonNum-1);
      }
    }
    // save the current reading for comparison
    // next time through the loop:
    lastReading[buttonNum-2] = currentReading[buttonNum-2];
  }

  // listen for Serial input on the TX/RX pins. This line
  // expects an ASCII-encoded numeric string:
  if (Serial1.available() > 0) {
    // read from the serial TX/RX pins:
    lastGroupNumber = Serial1.parseInt();
  }

  // check to see if serial value is greater than 0:
  if (lastGroupNumber > 0) {
    // set the LCD cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("group: ");
    // Print a message to the LCD.
    lcd.print(lastGroupNumber);
  }  
}




