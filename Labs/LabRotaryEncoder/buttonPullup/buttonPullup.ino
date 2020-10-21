void setup() {
  // set the encoder's pushbutton to use internal pullup resistor:
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(4);
  Serial.println(buttonState);
}
