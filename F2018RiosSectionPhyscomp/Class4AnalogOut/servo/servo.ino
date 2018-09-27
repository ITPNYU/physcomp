#include <Servo.h>
int reading;
Servo myservo;

int angle = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(2, INPUT);
}

void loop() {
  reading = analogRead(A0);
  angle = map(reading, 0, 1023, 0, 179);
  myservo.write(angle);

  Serial.println(angle);

}
