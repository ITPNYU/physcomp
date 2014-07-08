int myGroupNumber = 2;     // change this to your group number

void setup() {
  // initialize serial communiation:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  int serialValue = 0;
  // listen for Serial input. This line
  // expects an ASCII-encoded numeric string:
  if (Serial.available() > 0) {
    serialValue = Serial.parseInt();
  }

  // check to see if serial value is my group number:
  if (serialValue == myGroupNumber ) {
    // message was my group number
    // so generate physical output:
    digitalWrite(3, HIGH);
    Serial.print(myGroupNumber+1);
  }  
  else {
    // stop physical outut:
    digitalWrite(3, LOW); 
  }
}
