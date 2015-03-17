/*

Simple Serial Server
using serialport.js

To call this type the following on the command line:
node server.js portName

where portname is the name of your serial port, e.g. /dev/tty.usbserial-xxxx (on OSX)

created 19 Sept 2014
modified 17 Mar 2015
by Tom Igoe

*/

// include the various libraries that you'll use:
var serialport = require('serialport'), // include the serialportlibrary
  fs = require('fs'),                   // include the filesystem library
  http = require('http');							  // require HTTP library

// configure the serial port:
SerialPort = serialport.SerialPort,     // make a local instance of serialport
  portName = process.argv[2],           // get serial port name from the command line
  serialOptions = {                     // serial communication options
    baudRate: 9600,                     // data rate: 9600 bits per second
    parser: serialport.parsers.readline('\r\n') // return and newline generate data event
  };
var serialData = 0;  				            // variable to save latest data from serial port

// open the serial port:
var myPort = new SerialPort(portName, serialOptions);

// set up and start the server:
var server = http.createServer();	      // create a server
server.listen(8080);				            // start the server listening
server.on('request', respondToClient);  // set up an event listener for server event requests

// set up event listeners for the serial events:
myPort.on('open', showPortOpen);
myPort.on('data', saveLatestData);
myPort.on('error', showError);

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

// this is called whenever a client makes a request:
function respondToClient(request, response) {

  // if the client requests just '/', send the index.html page:
  if (request.url === '/') {
    response.writeHead(200, {"Content-Type": "text/html"});
    var fileStream = fs.createReadStream(__dirname + '/public/index.html');

    // event handlers for file reading:
    fileStream.on('data', writeFile);
    fileStream.on('end', closeConnection);

    function writeFile(data) {    // when you read data from the file,
      // log when serial data comes in (comment this out when running for real):
      // console.log("received from serial port: " + data);
      response.write(data);       // write it out to the client
    }

    function closeConnection() {  // when you reach the end of the file,
      response.end();             // close the connection to the client
    }
  }
  // if the client requests  '/data', send latest serial data:
  if (request.url === '/data') {
    // log when a client request comes in (comment this out when running for real):
    // console.log("Got a client request, sending them the data.");
    // respond to the client request with the latest serial data:
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.write(serialData);
    response.end();
  }
};
