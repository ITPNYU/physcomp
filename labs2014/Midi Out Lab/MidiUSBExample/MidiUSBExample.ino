#include <MIDIUSB.h>

// Variables:
byte note = 0;            // The MIDI note value to be played

void setup() {
  //  Set MIDI baud rate:
  Serial.begin(9600);
}

void loop() {
  // play notes from F#-0 (30) to F#-5 (90):
  for (note = 30; note < 90; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);
    delay(100);
  }
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(byte cmd, byte data1, byte data2) {
  // First parameter is the event type (top 4 bits of the command byte).
  // Second parameter is command byte combined with the channel.
  // Third parameter is the first data byte
  // Fourth parameter second data byte

  midiEventPacket_t midiMsg = {cmd >> 4, cmd, data1, data2};
  MidiUSB.sendMIDI(midiMsg);

  //prints the values in the serial monitor so we can see what note we're playing
  Serial.print("cmd: ");
  Serial.print(cmd);
  Serial.print(", data1: ");
  Serial.print(data1);
  Serial.print(", data2: ");
  Serial.println(data2);
}

