#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_SHTC3.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool showingTempAndHumidity = true;


void setup() {
  Serial.begin(115200);

  // Setting up SHTC3
  if (!shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
    while (1) delay(1);
  }
  Serial.println("Found SHTC3 sensor");

  // Setting up BMP390
  if (!bmp.begin_I2C()) {  // hardware I2C mode, can pass in address & alt Wire
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1)
      ;
  }
  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.cp437(true);                  // Use full 256 char 'Code Page 437' font

  // Setting up Adafruit_APDS9960
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  apds.enableProximity(true);
  apds.enableGesture(true);
}

void loop() {
  sensors_event_t humidity, temp;
  
  uint8_t gesture = apds.readGesture();
  if(gesture == APDS9960_LEFT || gesture == APDS9960_RIGHT){
    showingTempAndHumidity = !showingTempAndHumidity;
  }

  shtc3.getEvent(&humidity, &temp);  // populate temp and humidity objects with fresh data
  display.clearDisplay();
  display.setCursor(0, 0);
  if (showingTempAndHumidity) {
    display.println("Temperature: ");
    display.print(temp.temperature);
    display.println(" degree C");
    display.println("");

    display.println("Humidity: ");
    display.print(humidity.relative_humidity);
    display.println("% rH");
  }

  // Serial.println(bmp.performReading());
  if (!showingTempAndHumidity) {
    display.println("Pressure: ");
    display.print(bmp.pressure / 100.0);
    display.println(" hPa");
    display.println("");

    display.println("Approx.Altitude: ");
    display.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
    display.println(" m");
  }

  showingTempAndHumidity = !showingTempAndHumidity;
  display.display();
  delay(3000);
}