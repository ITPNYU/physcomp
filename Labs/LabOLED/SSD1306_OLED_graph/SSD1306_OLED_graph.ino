/*
  Minimal example for SSD1306 OLED display
  manufacturer's site: http://www.solomon-systech.com/en/product/advanced-display/oled-display-driver-ic/ssd1306/
  datasheet: https://www.crystalfontz.com/controllers/SolomonSystech/SSD1306/339/
  library: http://librarymanager/All#Adafruit_SSD1306

  These displays are common and inexpensive online, and require only the
  I2C pins (SDA and SCL) from an Arduino. The Adafruit library works well with them.

  This example reads the millis() and ana analog sensor and displays both.
  It's written for a 128x64 display, but can be modified to fit a 128x32 display as well.
  Change the SCREEN_HEIGHT to change displays, and adjust font sizes and cursor locations
  to suit your application.

  created 4 Oct 2021
  by Tom Igoe
  based on the Adafruit_SSD1306 library examples
*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels

// initialize the display:
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

int xPos = 0;
void setup() {
  // initialize serial and wait 3 secs for serial monitor to open:
  Serial.begin(9600);
  if (!Serial) delay(3000);
  // first parameter of begin() sets voltage source.
  // SSD1306_SWITCHCAPVCC is for 3.3V
  // second parameter is I2C address, which is
  // 0x3C, or 3D for some 128x64 modules:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display setup failed");
    while (true);
  }
  Serial.println("Display is good to go");
  // clear the display:
  display.clearDisplay();
}

void loop() {
  int sensorReading = analogRead(A0);
  int graphHeight = SCREEN_HEIGHT - map(sensorReading, 0, 1023, 0, SCREEN_HEIGHT);
  display.drawLine(xPos, SCREEN_HEIGHT, xPos, graphHeight, SSD1306_WHITE);
  xPos++;
  if (xPos > SCREEN_WIDTH) {
    xPos = 0;
    // clear the display:
    display.clearDisplay();
  }

  // push everything out to the screen:
  display.display();
}
