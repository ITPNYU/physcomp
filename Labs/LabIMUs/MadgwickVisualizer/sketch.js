/*
	p5.js Madgwick visualizer
	Based on Helena Bisby's Processing Madgwick visualizer

	Takes incoming serial data in the following form:
     Orientation: heading pitch roll
	Uses heading, pitch, and roll numbers (all floats)
	to position a 3D model of an Arduino Nano onscreen

	created 4 Aug 2019
	by Tom Igoe
*/

//  an instance of the serialport library:
let serial;
// fill in your serial port name here:
let portName = '/dev/cu.usbmodem141301';

// orientation variables:
let yaw = 0.0;
let pitch = 0.0;
let roll = 0.0;

// if there's new data from the microcontroller:
let newData = false;

function setup() {
	createCanvas(500, 600, WEBGL);
	// instantiate serial port:
	serial = new p5.SerialPort();
// set callback for port open:
	serial.on('open', startSerial);
	// set callback for incoming data:   
	serial.on('data', serialEvent);
	// open serial port:
	serial.open(portName);
}

function draw() {
	// if there's new data, update the drawing:
	if (newData) {
		background(255); // set background to white
		push(); // begin object
		// variables for matrix translation:
		let c1 = cos(radians(roll));
		let s1 = sin(radians(roll));
		let c2 = cos(radians(pitch));
		let s2 = sin(radians(pitch));
		let c3 = cos(radians(yaw));
		let s3 = sin(radians(yaw));
		applyMatrix(c2 * c3, s1 * s3 + c1 * c3 * s2, c3 * s1 * s2 - c1 * s3, 0,
			-s2, c1 * c2, c2 * s1, 0,
			c2 * s3, c1 * s2 * s3 - c3 * s1, c1 * c3 + s1 * s2 * s3, 0,
			0, 0, 0, 1);
		// draw arduino board:
		drawArduino();

		pop(); // end of object
		// you've used the new data:
		newData = false;
	}
}

// callback function for when serial port opens:
function startSerial() {
	// send an initial byte 
	// to get data from the microcontroller:
	serial.write('x');
	console.log('serial port opened');
}

// callback function for incoming serial data:
function serialEvent() {
	// read from port until new line:
	let message = serial.readStringUntil('\n');
	if (message != null) {
		let list = split(trim(message), " ");
		if (list.length >= 4 && list[0] == "Orientation:") {
			// convert list items to floats:
			yaw = float(list[1]);
			pitch = float(list[2]);
			roll = float(list[3]);
			// you have new valid data, so 
			// send a byte to get more:
			serial.write('x');
			// refresh newData:
			newData = true;
		}
	}
}
// draws the Arduino Nano:
function drawArduino() {
	// the base board:
	stroke(0, 90, 90); // set outline colour to darker teal
	fill(0, 130, 130); // set fill colour to lighter teal
	box(300, 10, 120); // draw Arduino board base shape

	// the CPU:
	stroke(0); // set outline colour to black
	fill(80); // set fill colour to dark grey
	translate(30, -6, 0); // move to correct position
	box(60, 0, 60);  // draw box

	// the radio module:
	stroke(80); // set outline colour to grey
	fill(180); // set fill colour to light grey
	translate(80, 0, 0); // move to correct position
	box(60, 15, 60); // draw box

	// the USB connector:
	translate(-245, 0, 0); // move to correct position
	box(35, 15, 40);	// draw box
}