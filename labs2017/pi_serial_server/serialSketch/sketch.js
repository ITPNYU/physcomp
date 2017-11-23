var serial; // instance of the serialport library
var portName = '/dev/ttyS0'; // fill in your serial port name here

var circleSize = 50;

function setup() {
  createCanvas(320, 240);
  // initalize serialport library to connect to p5.serialserver on the host:
  serial = new p5.SerialPort(document.location.hostname);
  // set callback functions for list and data events:
  serial.on('list', printList);
  serial.on('data', serialEvent);
  // open the serial port:
  serial.open(portName);
}

function draw() {
 background('#3399FF');
 fill('#DDFFFF');
 // draw a circle at the middle of the screen:
 ellipse(width/2, height/2, circleSize, circleSize);
}

function serialEvent() {
  // read a line of text in from the serial port:
  var data = serial.readLine();
  console.log(data);
  // if you've got a valid line, convert it to a number:
  if (data.length > 0) {
    circleSize = int(data) / 4;
  }
  // send a byte to the microcontroller
  // to prompt it to respond with another reading:
  serial.write('x');
}

function printList(portList) {
  // portList is an array of serial port names:
  for (var i = 0; i < portList.length; i++) {
    console.log(i + ' ' + portList[i]);
  }
}
