/*
  There's an LED and a pushbutton and a speaker attached
  to the Arduino for this sketch. Normally, the LED fades slowly
  from nothing to a dim level. When you press the button,
  the LED gets suddenly bright, and the speaker makes a
  plays a tone that gradually fades once you release the button.
  
  aka "laser shooty noise"
  
  created 24 Sept 2013
  by Tom Igoe

*/

int brightness = 0;      // brightness
int fadeChange = 1;      // brightness change amount
long lastFade = 0;       // last time you faded
int fadeDelay = 90;      // delay between fade steps

int pitch = 0;           // pitch
int pitchChange = 10;    // pitch change amount
long lastSound = 0;      // last time you changed the pitch
int soundDelay = 30;     // delay between pitch steps

void setup() {
  pinMode(2, INPUT);     // make the switch an input
}

void loop() {
  // if the button is pressed:
  if (digitalRead(2) == HIGH) {
    analogWrite(9, 255);         // make the LED bright
    pitch = 440;                 // set the pitch to middle A
  } 

  // if the pitch is above 10Hz
  if (pitch > 10) {
    makeSound();     // decrement the pitch
  }

  fadeLed();         // fade the LED
}



void fadeLed() {
  // if the fade delay has passed since the last time you faded:
  if (millis() - lastFade >= fadeDelay) {
    // increment the brightness using the fade change value:
    brightness = brightness + fadeChange;    
    // set the PWM level on the pin
    analogWrite(9, brightness);
    
    // if the brightness is at the bottom or top, 
    // change the direction of the fade change:
    if (brightness == 0 || brightness == 10) {
      fadeChange = -fadeChange; 
    }
    
    // save the time you last faded for next check:
    lastFade = millis(); 
  }  
}

void makeSound() {
  // if the sound delay has passed since the last time you changed pitch:
  if (millis() - lastSound >= soundDelay) {

    // decrement the brightness using the fade change value:
    pitch = pitch - pitchChange;
    // if the pitch is above 100, play it:
    if (pitch > 100) {
      tone(8, pitch);
    } 
    // if the pitch is below 100Hz, turn it off:
    else {
      noTone(8);
    }
    // save the time you last changed pitch for next check:
    lastSound = millis(); 
  }  
}



