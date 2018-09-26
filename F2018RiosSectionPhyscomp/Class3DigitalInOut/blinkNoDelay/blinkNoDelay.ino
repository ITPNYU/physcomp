int reading; // current button reading
int prevReading = 0;

int cT; // current Time
int previousTime = 0;

int ledR = 7;
int ledY = 6;
int ledG = 5;

int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);  // this is my button switch
  pinMode(ledR, OUTPUT); // this is my led
  pinMode(ledY, OUTPUT); // this is my led
  //  pinMode(ledG, OUTPUT); // this is my led
}

void loop() {

  reading = digitalRead(2);
  cT = millis();

  if (cT - previousTime > 500) {
    counter++;
    previousTime = millis();
  }

  if (counter == 0) {
    digitalWrite(ledR, LOW);
  } else {
    digitalWrite(ledR, HIGH);
  }

  if (reading == 1) {
    digitalWrite(ledY, HIGH);
  } else {
    digitalWrite(ledY, LOW);
  }

  counter = counter % 2;
  Serial.println(reading);
}






