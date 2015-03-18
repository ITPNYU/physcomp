/*

Simple Serial Server
using servi.js and p5.js

To call this type the following on the command line:
node index.js portName

where portname is the name of your serial port, e.g. /dev/tty.usbserial-xxxx (on OSX)

created 19 Sept 2014
modified 17 Mar 2015
by Tom Igoe

*/

var serialport = require('serialport'),// include the library
SerialPort = serialport.SerialPort,    // make a local instance of it
portName = process.argv[2];            // get port name from the command line

var serialData = 0;                    // latest data saved from the serial port

var servi = require('servi');          // include the servi library

var app = new servi(false);            // servi instance
app.port(8080);                        // port number to run the server on

// configure the server's behavior:
app.serveFiles("public");              // serve all static HTML files from /public
app.route('/data', sendData);          // route requests for /data to sendData() function
// now that everything is configured, start the server:
app.start();

var myPort = new SerialPort(portName, {
  baudRate: 9600,
  // look for return and newline at the end of each data packet:
  parser: serialport.parsers.readline('\r\n')
});

// these are the definitions for the serial events:
myPort.on('open', showPortOpen);
myPort.on('data', saveLatestData);
myPort.on('close', showPortClose);
myPort.on('error', showError);

// these are the functions called when the serial events occur:
function showPortOpen() {
  console.log('port open. Data rate: ' + myPort.options.baudRate);
}

function saveLatestData(data) {
  console.log(data);
  serialData = data;
}

function showPortClose() {
  console.log('port closed.');
}

function showError(error) {
  console.log('Serial port error: ' + error);
}

// ------------------------ Server function
function sendData(request) {
  // print out the fact that a client HTTP request came in to the server:
  console.log("Got a client request, sending them the data.");
  // respond to the client request with the latest serial string:
  request.respond(serialData);
}
