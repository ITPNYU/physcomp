int reading;
int led = 6;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}

void loop() {
  reading = analogRead(A0);
  digitalWrite(led, reading);
}
