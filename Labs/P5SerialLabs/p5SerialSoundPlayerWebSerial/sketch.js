/*
Serial read and sound playback
using p5.webserial and p5.sound.

Waits for serial to come in. Expects
a 1 or 0. Plays sound on 1.

Note: this sketch will not load as a local file.
You either need to use the p5.js web editor, or 
run a local web server,e.g.
python -m SimpleHTTPServer 

created 31 May 2022
by Tom Igoe
*/
// variable to hold an instance of the p5.webserial library:
const serial = new p5.WebSerial();

// HTML button object:
let portButton;
var song;                               // sound object for the sound file you want to play

function preload() {
  // soundFormats('mp3', 'ogg');
  song = loadSound('assets/ouch.mp3');
}

function setup() {
  createCanvas(400, 300);          // make the canvas
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
  serial.on("data", playOuch);
}

function draw() {
  background(0); // black background
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
  // wait for the serial.open promise to return,
  // then call the initiateSerial function
  serial.open().then(initiateSerial);

  // once the port opens, let the user know:
  function initiateSerial() {
    console.log("port open");
  }
  // hide the port button once a port is chosen:
  if (portButton) portButton.hide();
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