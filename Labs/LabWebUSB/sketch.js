/*
	p5.js Madgwick visualizer
	Based on Helena Bisby's Processing Madgwick visualizer

	Takes incoming serial data in the following form:
   heading,pitch,roll\n
	Uses heading, pitch, and roll numbers (all floats)
	to position a 3D model of an Arduino Nano onscreen

	created 4 Aug 2019
	modified 25 Aug 2019
	by Tom Igoe
*/

// //  an instance of the serialport library:
// let serial;
// // fill in your serial port name here:
// let portName = '/dev/cu.usbmodem1412201';

// orientation variables:
let heading = 0.0;
let pitch = 0.0;
let roll = 0.0;
let port;
let connectButton;

let textEncoder = new TextEncoder();

function setup() {
  createCanvas(500, 600, WEBGL);

  // Create a 'Connect' button
  connectButton = createButton('Connect')
  connectButton.mousePressed(discoverWebUSB);
}

function draw() {
  // update the drawing:
  background(255); // set background to white
  push(); // begin object to draw
  //variables for matrix translation:
  let c1 = cos(radians(roll));
  let s1 = sin(radians(roll));
  let c2 = cos(radians(pitch));
  let s2 = sin(radians(pitch));
  let c3 = cos(radians(heading));
  let s3 = sin(radians(heading));
  applyMatrix(c2 * c3, s1 * s3 + c1 * c3 * s2,
    c3 * s1 * s2 - c1 * s3, 0, -s2, c1 * c2,
    c2 * s1, 0, c2 * s3, c1 * s2 * s3 - c3 * s1,
    c1 * c3 + s1 * s2 * s3, 0, 0, 0, 0, 1);
  // draw arduino board:
  drawArduino();
  pop(); // end of object
}

function connect() {
  port.connect().then(() => {
    // change the name of the Connect button:
    connectButton.html('Disconnect');
    // Send initial byte to start the exchange;
    port.send(textEncoder.encode('x')).catch(error => {
      console.log('Send error: ' + error);
    });
    port.onReceive = serialEvent;
    // port.onReceive = data => {
    //   let textDecoder = new TextDecoder();
    //   console.log(textDecoder.decode(data));
    // };
    port.onReceiveError = error => {
      console.error(error);
    };
  }, error => {
    console.log(error);
  });
}

function discoverWebUSB() {
  if (port) {
    port.disconnect();
    // change the name of the Connect button:
    connectButton.html('Connect');
    port = null;
  } else {
    serial.requestPort().then(selectedPort => {
      port = selectedPort;
      connect();
    }).catch(error => {
      console.log(error);
    });
  }
}


// callback function for incoming serial data:
function serialEvent(data) {
  // read from port until new line:
  let textDecoder = new TextDecoder();
  let message = textDecoder.decode(data);
console.log(message);
  // let message = serial.readStringUntil('\n');
  //TODO: fill in webusb serial in here
  if (message != null) {
    let list = split(trim(message), ',');
    if (list.length >= 3) {
      // convert list items to floats:
      heading = float(list[0]);
      pitch = float(list[1]);
      roll = float(list[2]);
      //console.log(heading + ',' + pitch + ',' + roll);
      // send a byte to the microcontroller to get new data:
      // serial.write('x');
      port.send(textEncoder.encode('x')).catch(error => {
        console.log('Send error: ' + error);
      });
    }
  }
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
  box(60, 0, 60);  // draw box

  // the radio module:
  stroke(80); // set outline color to grey
  fill(180); // set fill color to light grey
  translate(80, 0, 0); // move to correct position
  box(60, 15, 60); // draw box

  // the USB connector:
  translate(-245, 0, 0); // move to correct position
  box(35, 15, 40);	// draw box
}