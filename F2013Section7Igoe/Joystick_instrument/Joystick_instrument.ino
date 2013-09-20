/*
 Simple musical instrument using Tone
 
 This example uses an analog input to set the pitch, and a digital
 input to play or stop the note.
 
 created 20 Sept 2013
 by Tom Igoe

*/


#include "pitches.h"

// notes in the octave:
int notes[] = {
  NOTE_C3, NOTE_CS3,NOTE_D3, NOTE_DS3, NOTE_E3,NOTE_F3, 
  NOTE_FS3, NOTE_G3,NOTE_GS3, NOTE_A4,NOTE_AS4, NOTE_A4};


void setup() {
  // make the select button an input:
  pinMode(2, INPUT);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A0);
  // map the sensor to the note range,
  // so you know which note of the note range to play:
  int whichNote = map(sensorReading, 0, 1023, 0, 11);
  // get the value of tne note to play:
  int noteToPlay = notes[whichNote];
  // if the select button is pressed:
  if (digitalRead(2) == HIGH) {
    //play the selected note
    tone(8, noteToPlay); 
  } // if the select button is not pressed
  else {
    // turn off the note
    noTone(8); 
  }
}


