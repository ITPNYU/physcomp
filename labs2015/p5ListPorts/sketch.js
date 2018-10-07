/*

Serial list ports

Lists serial ports in an options menu. When you choose one, opens the port
and displays any incoming strings as text onscreen.

Works with P5 editor as the serial server, version 0.5.5 or later.

created 2 Oct 2015
modified 7 Oct 2018
by Tom Igoe
*/

var serial;       // Declare a "SerialPort" object
var menu;         // a variable to hold the options menu
var textDiv;      // a variable to hold the text div for incoming data
var result = '';  // a variable for the incoming serial data

function setup() {
  noCanvas();
  createHTML();
  serial = new p5.SerialPort();
  serial.on('list', printList); 
  serial.on('data', printData);
}

function draw() {
  background(255);
  fill(0);
}

function createHTML() {
  // make an option menu for the serial ports:
  menu = createSelect();
  menu.option("Choose a serial port: ");
  menu.attribute('aria-label', 'Serial port selector');
  menu.position(10, 10);
  menu.changed(openPort);
// make a DOM element to take the incoming serial data:
  dataLabel = createElement('section', 'Incoming Serial Data');
  dataLabel.attribute('aria-label', 'serial input');
  dataLabel.position(10, 60);
}
function openPort() {
  portName = menu.elt.value;
  serial.open(portName);
}

function printData() {
  var inString = serial.readStringUntil('\r\n');
  trim(inString);
  if (!inString) return;
  result = inString;
  dataLabel.html(result);
}

// Got the list of ports
function printList(serialList) {
  for (var i = 0; i < serialList.length; i++) {
      menu.option(serialList[i]);
  }
}