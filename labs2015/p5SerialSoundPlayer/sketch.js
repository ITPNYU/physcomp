var song;                               // sound object for the sound file you want to play
var serial;                             // Declare a "SerialPort" object
var portName = '/dev/cu.usbmodem14121'; // fill in your serial port name here

function setup() {
  createCanvas(400,400);
  song = loadSound('ouch.mp3');   // load the sound file  
  serial = new p5.SerialPort();   // make an instance of the serial library
  serial.on('data', playOuch);    // declare serial data callback function

  serial.open(portName);          // open port
}

function playOuch() {
  var result = serial.readStringUntil('\r\n'); // read an ASCII-encoded string
  result = int(result);                        // convert it to a number
  if (result === 1) {                          // if it equals 1
    song.play();                               // play the sound file
  }
}