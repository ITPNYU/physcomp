
#include <Arduino_LSM6DS3.h>

// the orientation of the board last time through the loop:
int lastOrientation = 0;

void setup() {
  Serial.begin(9600);
 
  if (!IMU.begin()) {
    Serial.println("Failed to initialize the IMU sensor");
    // stop the program:
    while(true);
  }
}


void loop() {
  float x, y, z;
  int orientation;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    /*
      The orientations of the board:
      0: flat, processor facing up  (z axis is 1)
      1: flat, processor facing down (z axis is -1)
      2: facing left (y axis is 1)
      3: facing right (y axis is -1)
      4: USB connector up (x axis is 1)
      5: USB connector down (x axis is -1)
    */

    // if abs(z) is largest, you're on the Z axis:
    if ( abs(z) > abs(x) && abs(z) > abs(y)) {
      if (z > 0) {
        orientation = 0;
      } else {
        orientation = 1;
      }
    }
    // if abs(y) is largest, you're on the Y axis:
    if ( abs(y) > abs(x) && abs(y) > abs(z)) {
      if (y > 0) {
        orientation = 2;
      } else {
        orientation = 3;
      }
    }
    // if abs(x) is largest, you're on the y axis:
    if ( abs(x) > abs(y) && abs(x) > abs(z)) {
      if (x > 0) {
        orientation = 4;
      } else {
        orientation = 5;
      }
    }

    // if the orientation has changed, print out a description:
    if (orientation != lastOrientation) {
      Serial.print(orientation);
      switch (orientation) {
        case 0:  // flat, up
          Serial.println(": flat, facing up");
          break;
        case 1:  // flat, down
          Serial.println(": flat, facing down");
          break;
        case 2:  // facing left
          Serial.println(": facing right");
          break;
        case 3:  // facing right
          Serial.println(": facing left");
          break;
        case 4:  // USB up
          Serial.println(": facing USB up");
          break;
        case 5:  // USB down
          Serial.println(": facing USB down");
          break;
      }
      // save current orientation for comparison next time:
      lastOrientation = orientation;
    }
  }
}
