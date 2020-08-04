/*
  Minimal SD card datalogger with IMU

  This example shows how to log data from the Nano 33 IoT's 
  IMU sensor to an SD card using the SD library. 
  Contains only the bare minimum needed to write to the file. 
  There are no serial outputs, only the blinking LED.

  The circuit:
   Nano 33 IoT with SD card attached to SPI bus as follows:
 ** SDO - pin 11
 ** SDI - pin 12
 ** SCK - pin 13
 ** CS - pin 10 (for Nano and Uno; for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 1 Aug 2020
  by Tom Igoe
*/
#include <SD.h>
#include <Arduino_LSM6DS3.h>


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

  // if the card detect pin is false, no card:
  while (digitalRead(cardDetect) == LOW) {
    // toggle LED every 1/4 second while the SD card's not present:
    digitalWrite(LED_BUILTIN, HIGH);
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
  }

  // start the IMU:
  while (!IMU.begin()) {
    // toggle LED every 1/8 second while the sensor's not responding:
    digitalWrite(LED_BUILTIN, ledState);
    // change the LED state:
    ledState = !ledState;
    delay(125);
  }
  // turn the LED off:
  digitalWrite(LED_BUILTIN, LOW);
  // write a header to the SD card file:
  // note: the \ character allows you to extend a string
  // on another line in a C program:
  String dataString = "seconds, \
  x acceleration, \
  y accleration, \
  z acceleration, \
  x gyro, \
  y gyro, \
  z gyro";
  writeToSDCard(dataString);
}

void loop() {
  // read once a second:
  if (millis() - lastReading > 1000) {
    // make a string for assembling the data to log:
    String dataString = "";
    // add the current time in seconds:
    dataString += String(millis() / 1000);
    dataString += ",";

    // read your sensors:
    // values for acceleration & rotation:
    float xAcc, yAcc, zAcc;
    float xGyro, yGyro, zGyro;

    // if both accelerometer & gyrometer are ready to be read:
    if (IMU.accelerationAvailable() &&
        IMU.gyroscopeAvailable()) {
      // read accelerometer & gyrometer:
      IMU.readAcceleration(xAcc, yAcc, zAcc);

      // print the results:
      IMU.readGyroscope(xGyro, yGyro, zGyro);
      dataString += String(xAcc);
      dataString += ",";
      dataString += String(yAcc);
      dataString += ",";
      dataString += String(zAcc);
      dataString += ",";
      dataString += String(xGyro);
      dataString += ",";
      dataString += String(yGyro);
      dataString += ",";
      dataString += String(zGyro);
    }
    // write to the SD card:
    writeToSDCard(dataString);
  }  // end of if millis() statement
} // end of loop

void writeToSDCard(String inputString) {
  // open the file. Only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(fileName, FILE_WRITE);

  // if the file is available, write to it:
  // turn the LED on while writing and off when not writing too:
  if (dataFile) {
    digitalWrite(LED_BUILTIN, HIGH);
    dataFile.println(inputString);
    dataFile.close();
    digitalWrite(LED_BUILTIN, LOW);
    lastReading = millis();
  } else {
    // if the file can't be opened, leave the LED on:
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
