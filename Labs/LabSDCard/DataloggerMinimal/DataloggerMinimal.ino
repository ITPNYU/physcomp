/*
  Minimal SD card datalogger

  This example shows how to log data from two analog sensors
  to an SD card using the SD library. Contains only the bare
  minimum needed to write to the file. There are no serial outputs,
  only the blinking LED.

  The circuit:
   analog sensors on analog in A0, A1
   SD card attached to SPI bus as follows:
 ** SDO - pin 11
 ** SDI - pin 12
 ** SCK - pin 13
 ** CS - pin 10 (for Nano and Uno; for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 25 July 2020
  by Tom Igoe

  This example code is in the public domain.
*/
#include <SD.h>

// the SPI CS pin
const int chipSelect = 10;
const int cardDetect = 9;

// the filename. Use CSV so the result can be opened in a spreadsheet
const char fileName[] = "datalog.csv";
// time of last reading, in ms:
long lastReading = 0;

void setup() {
  // variable for the LED's state:
  int ledState = HIGH;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(cardDetect, INPUT);
  Serial.begin(9600);
  
  // if the card detect pin is false, no card:
  while (digitalRead(cardDetect) == LOW) {
    // toggle LED every 1/4 second while the SD card's not present:
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("no card");
  }
  // give the reader 5 seconds to settle the card once it's detected:
  delay(5000);
  
  // if the card is not present or cannot be initialized:
  while (!SD.begin(chipSelect)) {
    // toggle LED every 1/4 second while the SD card's not responding:
    digitalWrite(LED_BUILTIN, ledState);
    // change the LED state:
    ledState = !ledState;
    delay(250);
    Serial.println("no reader respnonseing");
  }
  // turn the LED off:
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {
  // read once a second:
  if (millis() - lastReading > 1000) {
    // make a string for assembling the data to log:
    String dataString = "";

    // read your sensors:
    int sensorOne = analogRead(A0);
    dataString += String(sensorOne);
    delay(1);
    // comma-separate the values:
    dataString += String(",");
    int sensorTwo = analogRead(A1);
    dataString += String(sensorTwo);
Serial.println("writing");
    // open the file. Only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open(fileName, FILE_WRITE);

    // if the file is available, write to it:
    // turn the LED on while writing and off when not writing too:
    if (dataFile) {
      digitalWrite(LED_BUILTIN, HIGH);
      dataFile.println(dataString);
      dataFile.close();
      digitalWrite(LED_BUILTIN, LOW);
      lastReading = millis();
    } else {
      // if the file can't be opened, leave the LED on:
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }  // end of if millis() statement
} // end of loop
