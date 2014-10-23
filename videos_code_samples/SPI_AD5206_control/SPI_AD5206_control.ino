/*
  AD5206 Digital potentiometer control
  Using the SPI library

  The AD5206 digital potentiometer expects two values via SPI:
  Channel number (0-5), value (0-255)

  Based on the Arduino SPI DigitalPotControl example
*/


// inslude the SPI library:
#include <SPI.h>

const int CSPin = 10;   // chip select pin number
int changeValue = 1;    // how much to change the pot each time
int potValue = 150;     //  pot value

void setup() {
  // initialize SPI:
  SPI.begin();
}

void loop() {

  // increment potValue using changeValue
  potValue = potValue + changeValue;
  
  // when potValue reaches extremes, reverse the
  // direction of change:
  if (potValue <= 150 || potValue >= 255) {
    changeValue = -changeValue;
  }

  // send the data via SPI:
  // take the Chip Select Pin low to select the chip:
  digitalWrite(CSPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(4);
  SPI.transfer(potValue);
  // take the Chip Select Pin high to de-select the chip:
  digitalWrite(CSPin, HIGH);

  tone(9, 440);
  delay(50);
}

