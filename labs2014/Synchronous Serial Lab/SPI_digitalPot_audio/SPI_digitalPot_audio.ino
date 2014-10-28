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
  tone(9, 440);
  for (int loudness = 0; loudness <= 255; loudness++) {
    digitalPotWrite(4, loudness);
    delay(20);
  }
  delay(1000);
  for (int loudness = 255; loudness >= 0; loudness--) {
    digitalPotWrite(4, loudness);
    delay(20);
  }
delay(1000);
}

void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(CSPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(CSPin, HIGH);
}
