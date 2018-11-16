/*
  A demonstration of how to manage output tasks on different time intervals
  using the millis() function

  created 25 Oct 2018
  by Tom Igoe

*/

// set pin numbers for three buttons, and three LEDs.
// the LEDs should be om PWM pins.
const int redButtonPin = 0;
const int greenButtonPin = 1;
const int blueButtonPin = 2;
const int redLed = 3;
const int greenLed = 4;
const int blueLed = 5;

// create variables for LED brightnesses:
int redBrightness, greenBrightness, blueBrightness = 0;

// create variables for LED fade timestamps:
long lastRedFade, lastGreenFade, lastBlueFade = 0;

// create variables for LED fade intervals:
long redInterval = 20;
long greenInterval = 10;
long blueInterval = 30;

void setup() {
  // set the input and output pin modes:
  pinMode(redButtonPin, INPUT);
  pinMode(greenButtonPin, INPUT);
  pinMode(blueButtonPin, INPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the pushbuttons:
  int redButtonState = digitalRead(redButtonPin);
  int greenButtonState = digitalRead(greenButtonPin);
  int blueButtonState = digitalRead(blueButtonPin);


  // if any button is pressed,
  // bump the corresponding LED brightness to full:
  if (redButtonState == HIGH) {
    redBrightness = 255;
  }
  if (greenButtonState == HIGH) {
    greenBrightness = 255;
  }
  if (blueButtonState == HIGH) {
    blueBrightness = 255;
  }
  
  // get the current time in millis:
  long now = millis();

  // fade the LEDs at three separate rates:
  // if the interval between fade steps has passed:
  if (now - lastRedFade > redInterval) {
    // if brightness > 0, decrement it by one:
    redBrightness = max(redBrightness--, 0);
    analogWrite(redLed, redBrightness);
    // save the current time for next interval comparison:
    lastRedFade = now;
  }
  if (now - lastGreenFade > greenInterval) {
    greenBrightness = max(greenBrightness--, 0);
    analogWrite(greenLed, greenBrightness);
    lastGreenFade = now;
  }
  if (now - lastBlueFade > blueInterval) {
    blueBrightness = max(blueBrightness--, 0);
    analogWrite(blueLed, blueBrightness);
    lastBlueFade = now;
  }
}
