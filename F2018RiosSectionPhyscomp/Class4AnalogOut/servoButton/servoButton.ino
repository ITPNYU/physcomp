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

  if (digitalRead(2) == 1) {
    angle++;
    //angle = constrain(angle, 0, 179);
  } else {
    angle--;
   // angle = constrain(angle, 0, 179);
  }

  myservo.write(angle);

  Serial.println(angle);

}
