/*
  Ultrasonic sensor example

  Ultrasonic sensors like the HC-SR04 operate by sending a short trigger pulse
  of 10 microseconds on the trigger pin, which then generates an ultrasonic pulse
  from the sensor. The echo pin goes high when the ultrasonic pulse is sent,
  and low when it returns. By measuring the time with pulseIn(),
  and knowing the speed of sound, you can determine the distance to the target.

  Circuit:
  - HC-SR-04 attached to +V and ground. For Nano 33 and other 3.3V boards,
  use the board's VUSB or +5V in. For Uno and 5V boards, use the 5V out.
  - HC-SR04 trigger pin attached to pin 9
  - HC-SR04 echo pin attached to pin 10

  based on example from Arduino Project Hub: https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
  modified 28 Sep 2020
  by Tom Igoe
  
*/
// set up pin numbers for echo pin and trigger pins:
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  // set the modes for the trigger pin and echo pin:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);

}

void loop() {
  // take the trigger pin low to start a pulse:
  digitalWrite(trigPin, LOW);
  // delay 2 microseconds:
  delayMicroseconds(2);
  // take the trigger pin high:
  digitalWrite(trigPin, HIGH);
  // delay 10 microseconds:
  delayMicroseconds(10);
  // take the trigger pin low again to complete the pulse:
  digitalWrite(trigPin, LOW);

  // listen for a pulse on the echo pin:
  long duration = pulseIn(echoPin, HIGH);
  // calculate the distance in cm.
  //Sound travels approx.0.0343 microseconds per cm.,
  // and it's going to the target and back (hence the /2):
  int distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  // a short delay between readings:
  delay(10);
}
