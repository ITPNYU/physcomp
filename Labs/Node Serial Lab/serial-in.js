/*

Simple Serial Server
using express.js and p5.js

To call this type the following on the command line:
node index.js portName

where portname is the name of your serial port, e.g. /dev/tty.usbserial-xxxx (on OSX)

created 19 Sept 2014
modified 26 July 2021
by Tom Igoe
*/

let SerialPort = require('serialport');     // include the serialport library
let	portName =  process.argv[2];            // get the port name from the command line

// if they didn't give a port name, tell them so, then quit:
if (!portName) {
  giveInstructions();
}

var myPort = new SerialPort(portName, 9600);// open the port
var Readline = SerialPort.parsers.Readline; // make instance of Readline parser
var parser = new Readline();                // make a new parser to read ASCII lines
myPort.pipe(parser);                        // pipe the serial stream to the parser

// these are the definitions for the serial events:
myPort.on('open', showPortOpen);    // called when the serial port opens
myPort.on('close', showPortClose);  // called when the serial port closes
myPort.on('error', showError);      // called when there's an error with the serial port
parser.on('data', readSerialData);  // called when there's new data incoming

// these are the functions called when the serial events occur:
function showPortOpen() {
  console.log('port open. Data rate: ' + myPort.baudRate);
}

function readSerialData(data) {
  console.log(data);
}

function showPortClose() {
  console.log('port closed.');
}

function showError(error) {
  console.log('Serial port error: ' + error);
}

function giveInstructions() {
    console.log('you did not give a port name');
    console.log('To run this properly, type \n');
    console.log('node serial-in.js portname\n');
    console.log('run the listPorts script to get a list of ports.\n');
    process.exit(0);
}
