/*

Serial sound player

Takes a serial input and uses it to play a sound. 
You can use this with the included Arduino example called buttonStateChange.\
Works with P5 editor as the serial server, version 0.5.5 or later.

Originally written for Processing, 2006?
modified 1 Oct 2015
by Tom Igoe
*/
var song;
var serial; // Declare a "SerialPort" object
var portName = '/dev/cu.usbmodem14121'; // fill in your serial port name here

var message = 'H';

function setup() {
  song = loadSound('ouch.mp3');
  // Instantiate our SerialPort object
  serial = new p5.SerialPort();

  // Let's list the ports available
  // You should have a callback defined to see the results
  serial.list();

  // Assuming our Arduino is connected, let's open the connection to it
  // Change this to the name of your arduino's serial port
  serial.open(portName);

  // When we some data from the serial port
  serial.on('data', playOuch);
}

function draw() {
  background(08, 24, 56);
  fill(200, 230, 250);
  ellipse(height / 2, width / 2, 50, 50);
}


function mousePressed() {
  if (message === 'H') {
    message = 'L';
    background(08, 24, 56)
  } else {
    message = 'H';
    background(140, 150, 155);
  }
  println(message);
  serial.write(message);
}

function openSocket() {
  serial.write("hello");
}


function playOuch(result) {
 var input = serial.read();
 if (input === '1') {
  song.play();
 }
}