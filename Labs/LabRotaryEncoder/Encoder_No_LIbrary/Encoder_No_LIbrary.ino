/*
  Rotary Encoder with no library. 
  Based on Paul Stoffregen's algorithm in the Encoder library
  See https://github.com/PaulStoffregen/Encoder/blob/eb73cf763504c6d0159fc2326fc9142a801e4e8a/Encoder.h#L187

  adapted from PJRC library 20 Jun 2022
  by Tom Igoe
*/

// pin numbers (use interrupt pins):
int pin1 = 2;
int pin2 = 3;
// encoder position and previous position:
volatile int position = 0;
int oldPosition = 0;
// state of the encoder switches:
volatile int state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin1), update, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin1), update, CHANGE);
}

void loop() {
  // if not using interrupts, include the line below:
  // update();
  int knobChange = position - oldPosition;
  int knobDirection = (knobChange / abs(knobChange));
  oldPosition = position;
  if (knobChange != 0) {
    Serial.println(knobDirection);
  }
}

void update() {
  // compare previous state with pins' default (INPUT_PULLUP):
  byte s = state & 0b11;
  delayMicroseconds(2000);
  // if pin 1 is high, set bit 2 of s high also:
  if (digitalRead(pin1)) s |= 0b100;
  // if pin 2 is high, set bit 3 of s high also:
  if (digitalRead(pin2)) s |= 0b1000;
  switch (s) {
    case 0:  // case 0, 5, 10, 15: no movement
    case 0b101:
    case 0b1010:
    case 0b1111:
      break;
    case 1:  //case 7, 8, 14: +1 step
    case 0b111:
    case 0b1000:
    case 0b1110:
      position++;
      break;
    case 0b10:  // case 4, 11, 13: -1 step
    case 0b100:
    case 0b1011:
    case 0b1101:
      position--;
      break;
    case 0b11:  // case 3, 12: +2 steps
    case 0b1100:
      position += 2;
      break;
    default:  // case 6, 9: -2 steps
      position -= 2;
      break;
  }
  // shift current state (s) into lower two bits
  // of state variable for comparison next time:
  state = (s >> 2);
}