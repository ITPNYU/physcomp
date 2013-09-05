/* 
 Serial String Reader
 Context: Processing
 
 Reads in a byte and graphs it.
 */
import processing.serial.*;

Serial myPort;              // the serial port
float xPos = 0;             // horizontal position of the graph

void setup() {
  size(800, 600);
  // list all the available serial ports
  println(Serial.list());

  // I know that the first port in the serial list on my Mac is always my
  // Arduino, so I open Serial.list()[0]. Open whatever port you're using
  // (the output of Serial.list() can help; the are listed in order
  // starting with the one that corresponds to [0]).
  myPort = new Serial(this, Serial.list()[0], 9600);

  // set inital background and smooth drawing:
  background(#081640);
  smooth();
}

void draw () {
}

// serialEvent method is run automatically by the Processing applet
// whenever the buffer reaches the byte value set in the bufferUntil() 
// method in the setup():
void serialEvent (Serial myPort) {
  int inByte = myPort.read();
  // convert to an int and map to the screen height:
  float sensorValue = map(inByte, 0, 255, 0, height);
  println(sensorValue);

  float yPos = height - sensorValue;
  // draw the line in a pretty color:
  stroke(#A8D9A7);
  line(xPos, height, xPos, height - sensorValue);

  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    background(#081640);
  } 
  else {
    // increment the horizontal position:
    xPos++;
  }
}

