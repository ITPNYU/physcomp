var serial;                             // variable to hold an instance of the serialport library
var portName = '/dev/cu.usbmodem14111';  // fill in your serial port name here
var inData;                           // for incoming serial data
var serialDiv;                        // an HTML div to show incoming serial data

function setup() {
	createCanvas(windowWidth, windowHeight);	// create a background canvas
	createHTML();                       // make some HTML to place incoming data into
	serial = new p5.SerialPort();       // make a new instance of the serialport library
	serial.on('data', serialEvent);     // callback for when new data arrives
	serial.open(portName);              // open a serial port
}

function draw() {
	// blue background:
	background('#1245ad');
}

function serialEvent() {
	// read a byte from the serial port, convert it to a number:
	inData = Number(serial.read());
	printData(inData);
}

// create some HTML elements in the sketch:
function createHTML() {
	serialDiv = createElement('p', 'incoming data goes here');
	serialDiv.attribute('aria-label', 'incoming data');
	serialDiv.attribute('aria-role', 'alert');
	serialDiv.attribute('aria-live', 'polite');
	serialDiv.style('color', 'white');
	serialDiv.position(10, 40);
}

function printData(inString) {
	// put the input in the serialDiv div:
	serialDiv.html('log: ' + inString);
}