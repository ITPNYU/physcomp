/*
Serial list ports using p5.webserial

Lists serial ports in a browser selection window. 
When you choose a port, it opens the port and 
displays any incoming strings as text in a text div. This makes
it accessible to screen readers.

created 31 May 2022
by Tom Igoe
*/

// variable to hold an instance of the p5.webserial library:
const serial = new p5.WebSerial();

// HTML button object:
let portButton;
// HTML div object for incoming text:
let incomingDiv;

function setup() {
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

  incomingDiv = createDiv("incoming text will go here");
  incomingDiv.position(10, 40);
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
  incomingDiv.html("port open")
  // hide the port button once a port is chosen:
  if (portButton) portButton.hide();
}

// read any incoming data as a string
// (assumes a newline at the end of it):
function serialEvent() {
  receivedText = serial.readLine();
  incomingDiv.html(receivedText);
}

// pop up an alert if there's a port error:
function portError(err) {
  alert("Serial port error: " + err);
}

// try to connect if a new serial port 
// gets added (i.e. plugged in via USB):
function portConnect() {
  incomingDiv.html("port connected");
  serial.getPorts();
}

// if a port is disconnected:
function portDisconnect() {
  serial.close();
  incomingDiv.html("port disconnected");
}