import processing.serial.*;

Serial myPort; 
int bgColor = 0;

void setup() 
{
  size(200, 200); 
  String portName = "/dev/tty.usbmodemfd1341";
  myPort = new Serial(this, portName, 9600);
}


void draw() {
  background(bgColor);
}
void mousePressed() {
 bgColor = 255; 
 myPort.write('H');
}

void mouseReleased() {
  bgColor = 0; 
  myPort.write('L');
}


