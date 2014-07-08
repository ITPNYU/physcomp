import processing.serial.*;

Serial myPort;
float xPos; 

void setup() {
  size(800, 600);
  //println(Serial.list()); 
  String portName = "/dev/tty.usbmodemfa13231";
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(0);
  fill(255);
  ellipse(xPos, height/2, 20, 20);
}

void serialEvent(Serial myPort) {
  float input = myPort.read();
  xPos = map(input, 0, 255, 0, width);
  myPort.write('x');
}

