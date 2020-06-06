var serial;                             // variable to hold an instance of the serialport library
var portName = '/dev/cu.usbmodem1412301';  // fill in your serial port name here
var inData;                             // for incoming serial data
var serialDiv;                        // an HTML div to show incoming serial data
function setup() {
  createCanvas(400, 300);
  createHTML();                       // make some HTML to place incoming data into
  serial = new p5.SerialPort();       // make a new instance of the serialport library
  serial.on('list', printList);       // set a callback function for the serialport list event
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen);        // callback for the port opening
  serial.on('data', serialEvent);     // callback for when new data arrives
  serial.on('error', serialError);    // callback for errors
  serial.on('close', portClose);      // callback for the port closing

  serial.list();                      // list the serial ports
  serial.open(portName);              // open a serial port
}

function draw() {
  // black background, white text:
  background(0);
  fill(255);
  // display the incoming serial data as a string:
  text("sensor value: " + inData, 30, 30);
  printData("sensor value: " + inData);
}
// get the list of ports:
function printList(portList) {
  // portList is an array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // Display the list the console:
    console.log(i + " " + portList[i]);
  }
}

function serverConnected() {
  console.log('connected to server.');
}

function portOpen() {
  console.log('the serial port opened.')
}

function serialEvent() {
  // read a byte from the serial port, convert it to a number:
  inData = Number(serial.read());
}

function serialError(err) {
  console.log('Something went wrong with the serial port. ' + err);
}

function portClose() {
  console.log('The serial port closed.');
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
  // print it to the console as well
 // console.log(inString);
}