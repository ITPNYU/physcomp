var song;                               // sound object for the sound file you want to play
var serial;                             // Declare a "SerialPort" object
var portName = '/dev/cu.usbmodem141231'; // fill in your serial port name here

function preload() {
  // soundFormats('mp3', 'ogg');
  song = loadSound('assets/ouch.mp3');
}

function setup() {
  createCanvas(400, 400);
  serial = new p5.SerialPort();   // make an instance of the serial library
  serial.on('data', playOuch);    // declare serial data callback function
  serial.open(portName);          // open port
}

function playOuch() {
  var inString = serial.readStringUntil('\r\n'); // read an ASCII-encoded string
  if (inString.length > 0) {
    var inData = Number(inString);                       // convert it to a number
    console.log(inData);
    if (inData === 1) {                          // if it equals 1
      song.play();                               // play the sound file
    }
  }
}