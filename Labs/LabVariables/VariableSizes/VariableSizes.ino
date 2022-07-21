void setup() {
  Serial.begin(9600);

  if (!Serial) delay(3000);
  Serial.print("byte:\t");
  Serial.print(sizeof(byte));
  Serial.println(" bytes");

  Serial.print("int:\t");
  Serial.print(sizeof(int));
  Serial.println(" bytes");

  Serial.print("float:\t");
  Serial.print(sizeof(float));
  Serial.println(" bytes");

   Serial.print("char:\t");
  Serial.print(sizeof(char));
  Serial.println(" bytes");

  Serial.print("long:\t");
  Serial.print(sizeof(long));
  Serial.println(" bytes");

 Serial.print("short:\t");
  Serial.print(sizeof(short));
  Serial.println(" bytes");


  Serial.print("double:\t");
  Serial.print(sizeof(double));
  Serial.println(" bytes");

  Serial.print("bool:\t");
  Serial.print(sizeof(bool));
  Serial.println(" bytes");

    Serial.print("String:\t");
  Serial.print(sizeof(String));
  Serial.println(" bytes (variable)");
}

void loop() {
  // put your main code here, to run repeatedly:
}