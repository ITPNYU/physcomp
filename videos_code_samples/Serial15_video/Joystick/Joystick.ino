/*
  Joystick reader
  Reads the value of the two analog outputs of a joystick
  and the one digital output of the joystick and prints
  them to the serial port.

  The joystick X and Y are  attached to pins A0 andA1.
  The joystick button is attached to digital pin 2.
*/

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // set pin 2 to be an input
  // and use the internal pullup resistor on that pin:
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  // read joystick's X axis:
  int x = analogRead(A0);
  // 1ms delay to let the ADC stabilize:
  delay(1);
  // read joystick's Y axis:
  int y = analogRead(A1);
  // 1ms delay to let the ADC stabilize:
  delay(1);
  // read the joystick's button:
  int button = digitalRead(2);
  // print the values from all three joystick outputs:
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(button);
}
