/*
Express Serial Server
using serialport.js and express.js

To call this type the following on the command line:
node server.js portName

where portname is the name of your serial port, e.g. /dev/tty.usbserial-xxxx (on OSX)

created 19 Sept 2014
modified 17 Mar 2015
by Tom Igoe
*/

// include the various libraries that you'll use:
var serialport = require('serialport'), // include the serialportlibrary
express = require('express'),           // include express.js
app = express();                        // a local instance of it

// configure the serial port:
SerialPort = serialport.SerialPort,     // make a local instance of serialport
portName = process.argv[2],             // get serial port name from the command line
serialOptions = {                       // serial communication options
  baudRate: 9600,                       // data rate: 9600 bits per second
  parser: serialport.parsers.readline('\r\n') // return and newline generate data event
};
var serialData = 0;                     // variable to save latest data from serial port

// open the serial port:
var myPort = new SerialPort(portName, serialOptions);

// set up event listeners for the serial events:
myPort.on('open', showPortOpen);
myPort.on('data', saveLatestData);
myPort.on('error', showError);

// Tell the server where files to serve are located:
app.use(express.static('public'));

// start the server:
var server = app.listen(8080);
// start the listener for client requests:
app.get('/data', sendData);        // handler for /date

// ------------------------ Serial event functions:
// this is called when the serial port is opened:
function showPortOpen() {
  console.log('port open. Data rate: ' + myPort.options.baudRate);
}

// this is called when new data comes into the serial port:
function saveLatestData(data) {
  // save the incoming serial data in serialData variable
  serialData = data;
}

// this is called when the serial port has an error:
function showError(error) {
  console.log('Serial port error: ' + error);
}

// ------------------------ Server event functions
// respond to the client request with the latest serial data:
function sendData(request, response) {
  response.send(serialData);
  response.end();
};
