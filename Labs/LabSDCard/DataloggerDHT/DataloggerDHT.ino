/*
  Minimal SD card datalogger with DHT11 or DHT22 temperature
  and humidity sensor

  This example shows how to log data from the DHT temperature and
  hhumidity sensors to an SD card using the SD library.
  Contains only the bare minimum needed to write to the file.
  There are no serial outputs, only the blinking LED.

  It  uses the Adafruit DHT sensor library from
  https://github.com/adafruit/DHT-sensor-library

  The circuit:
   Nano 33 IoT with SD card attached to SPI bus as follows:
 ** SDO - pin 11
 ** SDI - pin 12
 ** SCK - pin 13
 ** CS - pin 10 (for Nano and Uno; for MKRZero SD: SDCARD_SS_PIN)
   DHT11 sensor connected as follows:
 ** Ground connected to ground
 ** Voltage connected to Vcc
 ** data out connected to 7
 ** 10K resistor connected from 7 to +Vcc

  created  24 Nov 2010
  modified 1 Aug 2020
  by Tom Igoe
*/
#include <SD.h>
#include "DHT.h"

// what pin the sensor is connected to:
#define DHTPIN 7
// Which type of DHT sensor you're using:
#define DHTTYPE DHT11

// Properties of the DHT sensor:
#define TEMPERATURE 1
#define HUMIDITY 0

// initialize the sensor:
DHT dht(DHTPIN, DHTTYPE);

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

  // start the sensor:
  dht.begin();

  // turn the LED off:
  digitalWrite(LED_BUILTIN, LOW);
  // write a header to the SD card file:
  // note: the \ character allows you to extend a string
  // on another line in a C program:
  String dataString = "seconds, \
  temperature, \
  humidity";
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

    // read the sensor:
    float temperature =  readSensor(TEMPERATURE);
    float humidity = readSensor (HUMIDITY);
    dataString += String(humidity);
    dataString += ",";
    dataString += String(temperature);

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


// get the sensor readings:
float readSensor( int thisValue) {
  float result;

  if (thisValue == TEMPERATURE) {
    result = dht.readTemperature();
  }
  else if (thisValue == HUMIDITY) {
    // read sensor:
    result = dht.readHumidity();
  }

  // make sure you have good readings. If the reading
  // is not a number (NaN) then return an error:
  if (isnan(result)) {
    // an impossible result for either reading
    // so it'll work as an error:
    result = -273.15;
  }
  return result;
}
