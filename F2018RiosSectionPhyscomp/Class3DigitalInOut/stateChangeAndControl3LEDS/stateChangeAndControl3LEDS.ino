int reading; // current button reading
int prevReading = 0 ; // prevous reading

int ledR = 7;   // pin of red led
int ledY = 6;   // pin of yellow led
int ledG = 5;   // pin of green led

int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);  // this is my button switch
  pinMode(ledR, OUTPUT); // this is my red led
  pinMode(ledY, OUTPUT); // this is my yellow led
  pinMode(ledG, OUTPUT); // this is my green led
}

void loop() {
  reading = digitalRead(2); // read the current state of the switch
  Serial.println(reading); // print the current state of the switch

// if our button is currently being pressed
  if (reading == 1) {
    if (prevReading == 1) {} // its still on ..... forever. 

    if (prevReading == 0) { // JUST PRESSED
      prevReading = 1;      // UPDATE PREVIOUS
    }
  }
// if our button is currently not being pressed
  if (reading == 0) {
    if (prevReading == 0) {} // Has not been pressed recently
    if (prevReading == 1) { // JUST RELEASED
      counter++;     // update our counter which will control our led output
      prevReading =0;
    }
  }

// Different LED conditions
  if (counter == 0) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
  }

  if (counter == 1) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
  }

  if (counter == 2) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, HIGH);
    digitalWrite(ledG, LOW);
  }

  if (counter == 3) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, HIGH);
  }
  if (counter == 4) { 
    counter = 0;  // reset the counter
  }
}
