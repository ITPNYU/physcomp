import processing.serial.*;

Serial myPort;
float xPos; 
float yPos;

void setup() {
  size(800, 600);
  //println(Serial.list()); 
  String portName = "/dev/tty.usbmodemfa13231";
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  fill(255);
  ellipse(xPos, yPos, 20, 20);
}

void serialEvent(Serial myPort) {
  String input = myPort.readString();
  String[] numbers = split(input, ',');
  float[] values = float(numbers);
  xPos = map(values[0], 0, 1023, 0, width);
  yPos = map(values[1], 0, 1023, 0, height);
  myPort.write('x');
}

