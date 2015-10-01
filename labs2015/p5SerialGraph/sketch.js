/*

Serial graphing

Takes a serial input, expecting an ASCII-encoded number followed by return and newline
Assumes the value will be between 0 and 1023. 
You can use this with the built-in Arduino example called AnalogReadSerial.
Graphs the result.

Works with P5 editor as the serial server, version 0.5.5 or later.

Originally written for Processing, 2006?
modified 1 Oct 2015
by Tom Igoe
*/


var serial;                               // Declare a "SerialPort" object
var xPos = 0;                             // x position of the graph
var portName = '/dev/cu.usbmodem14121';   // fill in your serial port name here
function setup() {
  createCanvas(800, 600); // window size
  println(height);
  smooth();
  // change the number below to match your port:
  background(0x08, 0x16, 0x40);

  // Instantiate our SerialPort object
  serial = new p5.SerialPort();

  // Let's list the ports available
  // You should have a callback defined to see the results
  serial.list();

  // Assuming our Arduino is connected, let's open the connection to it
  // Change this to the name of your arduino's serial port
  serial.open(portName);

  // Here are the callbacks that you can register

  // When we connect to the underlying server
  serial.on('connected', serverConnected);

  // When we get a list of serial ports that are available
  serial.on('list', gotList);

  // When we some data from the serial port
  serial.on('data', graphData);

  // When or if we get an error
  serial.on('error', gotError);

  // When our serial port is opened and ready for read/write
  serial.on('open', graphData);
}

// We are connected and ready to go
function serverConnected() {
  // Let's list the ports available
  serial.list();
}

// Got the list of ports
function gotList(thelist) {
  // theList is an array of their names
  for (var i = 0; i < thelist.length; i++) {
    // Display in the console
    println(i + " " + thelist[i]);
  }
}

// Connected to our serial device
function gotOpen() {
  println("Serial Port is Open!");
}

// Uh oh, here is an error, let's log it
function gotError(theerror) {
  println(theerror);
}


function graphData() {
  var inString = serial.readStringUntil('\r\n');
  inString.trim();
  // if the string is empty, exit this function:
  if (inString === "") return;
  // print it:
  //println(inString);
  // map the range of the input to the window height:
  var yPos = map(inString, 0, 1023, 0, height);
  // draw the line in a pretty color:
  stroke(0xA8, 0xD9, 0xA7);
  line(xPos, height, xPos, height - yPos);
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    // clear the screen by resetting the background:
    background(0x08, 0x16, 0x40);
  } else {
    // increment the horizontal position for the next reading:
    xPos++;
  }
}