#include <Encoder.h>

// encoder on pins 2 and 3
Encoder myEncoder(2, 3);
// previous position of the encoder:
int lastPosition = 0;

// steps of the encoder's shaft:
int steps = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int newPosition = myEncoder.read();
  // compare current and last encoder state:
  int change = newPosition - lastPosition;
  // if it's changed by 4 or more (one detent step):
  if (abs(change) >= 4) {
    // get the direction (-1 or 1):
    int encoderDirection = (change / abs(change));
    steps += encoderDirection;
    // if you want to make the steps rollover, use this:
    steps = steps % 24;
    Serial.println(steps);

    // save encoder position for next time through loop:
    lastPosition = newPosition;
  }
}
