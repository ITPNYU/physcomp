int reading;
int freq;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT);

}

void loop() {
  reading = analogRead(A0);
  freq = map(reading, 0 , 1023, 40, 3000);
  Serial.println(reading);
  if (digitalRead(2) == 1) {
    tone(9, freq);
  } else {
    noTone(9);
  }


}
