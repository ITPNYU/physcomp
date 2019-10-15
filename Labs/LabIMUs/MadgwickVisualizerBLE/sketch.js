/*
	p5.js Madgwick visualizer
	Based on Helena Bisby's Processing Madgwick visualizer

	Takes incoming BLE data for heading, pitch, and roll
	Uses these numbers (all floats)
	to position a 3D model of an Arduino Nano onscreen

	Note: this sketch currently uses a MODIFIED version of p5.ble.min.js. it replaces 
	r=n.getFloat32(0);
	with
	r=n.getFloat32(0, true);

	Watch https://github.com/ITPNYU/p5.ble.js for updates.

	created 13 Aug 2019
	modified 7 Oct 2019
	by Tom Igoe
*/
// UUIDs for the service and the three characteristics:
const serviceUuid = '23ce3f92-be01-11e9-9cb5-2a2ae2dbcce4';
const headingUuid = '23ce450a-be01-11e9-9cb5-2a2ae2dbcce4';
const pitchUuid = '23ce4276-be01-11e9-9cb5-2a2ae2dbcce4';
const rollUuid = '23ce43ca-be01-11e9-9cb5-2a2ae2dbcce4';

// instance of p5.ble, to access the peripheral:
let myPeripheral;
let connectButton;

// orientation variables:
let heading = 0.0;
let pitch = 0.0;
let roll = 0.0;

// if there's new data from the microcontroller:
let newData = false;

function setup() {
	createCanvas(500, 600, WEBGL);
	// Create a p5ble class
	myPeripheral = new p5ble();

	// Create a 'Connect' button
	connectButton = createButton('Connect')
	connectButton.mousePressed(connectToBle);
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
		let c3 = cos(radians(heading));
		let s3 = sin(radians(heading));
		applyMatrix(c2 * c3, s1 * s3 + c1 * c3 * s2, c3 * s1 * s2 - c1 * s3, 0,
			-s2, c1 * c2, c2 * s1, 0,
			c2 * s3, c1 * s2 * s3 - c3 * s1, c1 * c3 + s1 * s2 * s3, 0,
			0, 0, 0, 1);
		// draw arduino board:
		drawArduino();

		pop(); // end of object
		// you've used the new data:
		// console.log(heading + "   " + pitch + "   " + roll);
		newData = false;
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

function connectToBle() {
	// if peripheral is not connected, connect:
	if (!myPeripheral.isConnected()) {
		// Connect to the peripheral by passing the service UUID
		myPeripheral.connect(serviceUuid, gotCharacteristics);

	} else {
		// if the peripheral is connected, disconnect:
		myPeripheral.disconnect();
	}
}

// disconnect handler for the peripheral"
function handleDisconnect() {
	// change the name of the Connect button:
	connectButton.html('Connect');
}

// A function that will be called once got characteristics
function gotCharacteristics(error, characteristics) {
	if (error) console.log('error: ', error);
	// change the name of the Connect button:
	connectButton.html('Disconnect');
	// set a disconnect handler for the peripheral:
	myPeripheral.onDisconnected(handleDisconnect);

	console.log('characteristics: ', characteristics);

	// iterate over the characteristics, and if they match the 
	// orientation characteristics' UUIDs, set listeners for them:
	for (c in characteristics) {
		thisUuid = characteristics[c].uuid;
		if (thisUuid === headingUuid) {
			myPeripheral.startNotifications(characteristics[c], getHeading, 'float32');
		} else if (thisUuid === pitchUuid) {
			myPeripheral.startNotifications(characteristics[c], getPitch, 'float32');
		} else if (thisUuid === rollUuid) {
			myPeripheral.startNotifications(characteristics[c], getRoll, 'float32');
		}
	}
}

// listener for heading characteristic notifications:
function getHeading(data) {
	heading = data;
	newData = true;
}
// listener for pitch characteristic notifications:
function getPitch(data) {
	pitch = data;
	newData = true;
}

// listener for roll characteristic notifications:
function getRoll(data) {
	roll = data;
	newData = true;
}