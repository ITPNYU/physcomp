import processing.serial.*;

Serial myPort; 
int xPos = 0;

void setup() 
{
  size(200, 200); 
  String portName = "/dev/tty.usbmodemfd1341";
  myPort = new Serial(this, portName, 9600);
}


void draw() {
  background(0);
  fill(255);
  ellipse(xPos, height/2, 20, 20);
}

void serialEvent(Serial myPort) {
  if (myPort.available()>0) {
    xPos = myPort.read(); 
  }
}
