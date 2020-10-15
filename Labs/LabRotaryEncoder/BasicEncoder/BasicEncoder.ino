#include <Encoder.h>

// encoder on pins 2 and 3
Encoder myEncoder(2, 3);
// previous position of the encoder:
int lastPosition = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long newPosition = myEncoder.read();
  if (newPosition != lastPosition) {
    lastPosition = newPosition;
    Serial.print("position: ");
    Serial.write(newPosition);
    Serial.print("  ");
    Serial.println(newPosition);
  }
}
