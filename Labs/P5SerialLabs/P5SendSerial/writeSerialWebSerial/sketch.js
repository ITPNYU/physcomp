/*
Serial write using p5.webserial

Sends binary byte values out on mouse drag or
key press '0' to '9'. Reads bytes in and interprets
them as binary values

created 31 May 2022
by Tom Igoe
*/
// variable to hold an instance of the p5.webserial library:
const serial = new p5.WebSerial();

// HTML button object:
let portButton;
let inData;                            // for incoming serial data
let outByte = 0;                       // for outgoing data

function setup() {
  createCanvas(400, 300);          // make the canvas
   // check to see if serial is available:
   if (!navigator.serial) {
    alert("WebSerial is not supported.");
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
}
function draw() {
  // black background, white text:
  background(0);
  fill(255);
  // display the incoming serial data as a string:
  text("incoming value: " + inData, 30, 30);
}

function mouseDragged() {
  // map the mouseY to a range from 0 to 255:
  outByte = int(map(mouseY, 0, height, 0, 255));
  // send it out the serial port:
  serial.write(outByte);
}

function keyPressed() {
  if (key >=0 && key <=9) {   // if the user presses 0 through 9
    outByte = byte(key * 25); // map the key to a range from 0 to 225
  }
  serial.write(outByte);      // send it out the serial port
}

function serialEvent() {
  // read a byte from the serial port:
  var inByte = serial.read();
  // store it in a global variable:
  inData = inByte;
}

// if there's no port selected, 
// make a port select button appear:
function makePortButton() {
  // create and position a port chooser button:
  portButton = createButton('choose port');
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
  serial.open();
  console.log("port open")
  // hide the port button once a port is chosen:
  if (portButton) portButton.hide();
}

// read any incoming data as a byte:
function serialEvent() {
  // read a byte from the serial port:
  var inByte = serial.read();
  // store it in a global variable:
  inData = inByte;
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
