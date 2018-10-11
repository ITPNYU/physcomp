/*
Serial list ports

Lists serial ports in an options menu. When you choose one, opens the port
and displays any incoming strings as text in a text div. This makes
it accessible to screen readers.

Works with P5 editor as the serial server, version 0.5.5 or later.

created 2 Oct 2015
modified 8 Oct 2018
by Tom Igoe
*/

var serial;       // Declare a "SerialPort" object
var menu;         // a variable to hold the options menu
var result = '';  // a variable for the incoming serial data
var serialInput;  // a div for incoming serial data
var hidden = false; // whether the serial controls are hidden or not

function setup() {
  // create some HTML elements to manage serial input:
  createHTML();
  // open an instance of serialport and set up event handlers:
  serial = new p5.SerialPort();
  serial.on('list', printList);
  serial.on('data', printData);
}

// nothing happens in the draw function, since it's all 
// based on serial input and keyboard input:
function draw() {

}

function createHTML() {
  // make an option menu for the serial ports:
  menu = createSelect();
  menu.option("Choose a serial port: ");
  menu.attribute('aria-label', 'Serial port selector');
  menu.position(10, 30);
  menu.changed(openPort);
  // get the DOM element for showing incoming serial data:
  serialInput = document.getElementById('serial');
  // convert it to a p5.elt so we can use the p5 DOM functions on it:
  serialInput = new p5.Element(serialInput);
}

function openPort() {
  // get the value of the option chosen from the select menu:
  portName = menu.elt.value;
  // open the port:
  serial.open(portName);
  // notify the user in the HTML div:
  serialInput.html('Serial port ' + portName + ' is open.')
}

function printData() {
  // read serial input:
  var inString = serial.readStringUntil('\r\n');
  // trim any whitespace:
  trim(inString);
  // if there's no string, quit this function:
  if (!inString) return;
  // put the result in the serialInput div:
  serialInput.html(inString);
  console.log(inString);
}

// Got the list of ports
function printList(serialList) {
  // add serial port list items to the options menu:
  for (var i = 0; i < serialList.length; i++) {
    menu.option(serialList[i]);
  }
}

function keyReleased() {
  // if the spacebar is pressed, show or hide the serial menu and display div
  if (key == ' ') {
    if (!hidden) {
      serialInput.hide();
      menu.hide();
    } else {
      serialInput.show();
      menu.show();
    }
    hidden = !hidden;
  }
}