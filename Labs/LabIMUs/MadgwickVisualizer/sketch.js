/*
	p5.js Madgwick visualizer
	Based on Helena Bisby's Processing Madgwick visualizer

	Takes incoming serial data in the following form:
	 heading,pitch,roll\n
	Uses heading, pitch, and roll numbers (all floats)
	to position a 3D model of an Arduino Nano onscreen

	created 4 Aug 2019
	modified 12 Jun 2022
	by Tom Igoe
*/

// variable to hold an instance of the p5.webserial library:
const serial = new p5.WebSerial();

// HTML button object:
let portButton;

// orientation variables:
let heading = 0.0;
let pitch = 0.0;
let roll = 0.0;

function setup() {
  createCanvas(500, 600, WEBGL); // make the canvas
  // check to see if serial is available:
  if (!navigator.serial) {
    alert("WebSerial is not supported in this browser. Try Chrome or MS Edge.");
  }
  // if serial is available, add connect/disconnect listeners:
  navigator.serial.addEventListener("connect", portConnect);
  navigator.serial.addEventListener("disconnect", portDisconnect);
  // check for any ports that are available:
  serial.getPorts();
  // if there's no port chosen, choose one:
  serial.on("noport", makePortButton);
  // open whatever port is available:
  serial.on("portavailable", openPort);
  // handle serial errors:
  serial.on("requesterror", portError);
  // handle any incoming serial data:
  serial.on("data", serialEvent);
  serial.on("close", makePortButton);
}

function draw() {
  // update the drawing:
  background(255); // set background to white
  push(); // begin object to draw

  // variables for matrix translation:
  let c1 = cos(radians(roll));
  let s1 = sin(radians(roll));
  let c2 = cos(radians(pitch));
  let s2 = sin(radians(pitch));
  let c3 = cos(radians(heading));
  let s3 = sin(radians(heading));
  applyMatrix(
    c2 * c3,
    s1 * s3 + c1 * c3 * s2,
    c3 * s1 * s2 - c1 * s3,
    0,
    -s2,
    c1 * c2,
    c2 * s1,
    0,
    c2 * s3,
    c1 * s2 * s3 - c3 * s1,
    c1 * c3 + s1 * s2 * s3,
    0,
    0,
    0,
    0,
    1
  );

  // draw arduino board:
  drawArduino();
  pop(); // end of object
}

// draws the Arduino Nano:
function drawArduino() {
  // the base board:
  stroke(0, 90, 90); // set outline color to darker teal
  fill(0, 130, 130); // set fill color to lighter teal
  box(300, 10, 120); // draw Arduino board base shape

  // the CPU:
  stroke(0); // set outline color to black
  fill(80); // set fill color to dark grey
  translate(30, -6, 0); // move to correct position
  box(60, 0, 60); // draw box

  // the radio module:
  stroke(80); // set outline color to grey
  fill(180); // set fill color to light grey
  translate(80, 0, 0); // move to correct position
  box(60, 15, 60); // draw box

  // the USB connector:
  translate(-245, 0, 0); // move to correct position
  box(35, 15, 40); // draw box
}

// if there's no port selected,
// make a port select button appear:
function makePortButton() {
  // create and position a port chooser button:
  portButton = createButton("choose port");
  portButton.position(10, 10);
  // give the port button a mousepressed handler:
  portButton.mousePressed(choosePort);
}

// make the port selector window appear:
function choosePort() {
  serial.requestPort();
}

// open the selected port, and make the port
// button invisible:
function openPort() {
  // wait for the serial.open promise to return,
  // then call the initiateSerial function
  serial.open().then(initiateSerial);

  // once the port opens, let the user know:
  function initiateSerial() {
    console.log("port open");
    serial.write("x");
  }
  // hide the port button once a port is chosen:
  if (portButton) portButton.hide();
}

// read any incoming data:
function serialEvent() {
  // read from port until new line:
  let inString = serial.readStringUntil("\r\n");
  if (inString != null) {
    let list = split(trim(inString), ",");
    if (list.length > 2) {
      // conver list items to floats:
      heading = float(list[0]);
      pitch = float(list[2]);
      roll = float(list[1]);
      // send a byte to the microcontroller to get new data:
      serial.write("x");
    }
  }
}

// pop up an alert if there's a port error:
function portError(err) {
  alert("Serial port error: " + err);
}

// try to connect if a new serial port
// gets added (i.e. plugged in via USB):
function portConnect() {
  console.log("port connected");
  serial.getPorts();
}

// if a port is disconnected:
function portDisconnect() {
  serial.close();
  console.log("port disconnected");
}
