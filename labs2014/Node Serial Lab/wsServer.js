/*

Simple Serial-to-websocket Server
using serialport.js

To call this type the following on the command line:
node wsServer.js portName

where portname is the name of your serial port, e.g. /dev/tty.usbserial-xxxx (on OSX)

created 28 Aug 2015
by Tom Igoe

*/

// include the various libraries that you'll use:
var serialport = require('serialport'),   // include the serialport library
  WebSocketServer = require('ws').Server; // include the webSocket library

// configure the webSocket server:
var SERVER_PORT = 8081;                 // port number for the webSocket server
var wss = new WebSocketServer({port: SERVER_PORT}); // the webSocket server
var connections = new Array;            // list of connections to the server

// configure the serial port:
SerialPort = serialport.SerialPort,     // make a local instance of serialport
portName = process.argv[2],             // get serial port name from the command line
serialOptions = {                       // serial communication options
  baudRate: 9600,                       // data rate: 9600 bits per second
  parser: serialport.parsers.readline('\n') // newline generates a data event
};

// open the serial port:
if (typeof portName === "undefined") {
  console.log("You need to specify the serial port when you launch this script, like so:\n");
  console.log("    node wsServer.js <portname>");
  console.log("\n Fill in the name of your serial port in place of <portname> \n");
  process.exit(1);
}
var myPort = new SerialPort(portName, serialOptions);

// set up event listeners for the serial events:
myPort.on('open', showPortOpen);
myPort.on('data', sendSerialData);
myPort.on('error', showError);

// ------------------------ Serial event functions:
// this is called when the serial port is opened:
function showPortOpen() {
  console.log('port open. Data rate: ' + myPort.options.baudRate);
}

// this is called when new data comes into the serial port:
function sendSerialData(data) {
  // if there are webSocket connections, send the serial data
  // to all of them:
  if (connections.length > 0) {
    broadcast(data);
  }
}

// this is called when the serial port has an error:
function showError(error) {
  console.log('Serial port error: ' + error);
}

function sendToSerial(data) {
  console.log("sending to serial: " + data);
  myPort.write(data);
}

// ------------------------ webSocket Server event functions
wss.on('connection', handleConnection);

function handleConnection(client) {
  console.log("New Connection");        // you have a new client
  connections.push(client);             // add this client to the connections array

  client.on('message', sendToSerial);      // when a client sends a message,

  client.on('close', function() {           // when a client closes its connection
    console.log("connection closed");       // print it out
    var position = connections.indexOf(client); // get the client's position in the array
    connections.splice(position, 1);        // and delete it from the array
  });
}
// This function broadcasts messages to all webSocket clients
function broadcast(data) {
  for (c in connections) {     // iterate over the array of connections
    connections[c].send(data); // send the data to each connection
  }
}
