import processing.serial.*;

Serial myPort;
float xPos; 

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
  ellipse(xPos, height/2, 20, 20);
}

void serialEvent(Serial myPort) {
  String input = myPort.readString();
  float value = float(input);
  xPos = map(value, 0, 1023, 0, width);
  myPort.write('x');
}

