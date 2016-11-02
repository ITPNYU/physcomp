/*
	Serial in binary
  Uses a call-and-response approach to receive a binary
  two-byte value from the serial port.
  
  created 2 Nov 2016
  by Tom Igoe
*/

var serial; // variable to hold an instance of the serialport library
var sensorValue;

function setup() {
  createCanvas(320, 240);
  serial = new p5.SerialPort(); // make a new instance of  serialport library
  serial.on('data', serialEvent); // callback for new data coming in
  serial.on('open', portOpen);		// callback for port opening
  serial.open("/dev/cu.usbmodem142441"); // open a port
}

function draw() {
  background(220);
  fill(0);
  text("From Arduino:  " + sensorValue, 10, 30);
}

// when the serial connection first opens, send a byte
// to get the microcontroller started sending:
function portOpen() {
 serial.write('x'); 
}

function serialEvent() {
  // wait for two bytes before interpreting:
  if (serial.available() > 1) {
    // high byte is the first byte that the microcontroller sent:
    var highByte = Number(serial.read());
    // low byte is the second byte sent:
    var lowByte = Number(serial.read());
    // combine the two bytes into one value: 
    sensorValue = highByte * 256 + lowByte;
    // send another byte to get a new reading:
    serial.write('x');
  }
}