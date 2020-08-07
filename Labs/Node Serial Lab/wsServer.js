/*
Serial-to-websocket Server
using serialport.js

To call this type the following on the command line:
node wsServer.js portName

where portname is the name of your serial port, e.g. /dev/tty.usbserial-xxxx (on OSX)

created 28 Aug 2015
modified 6 Aug 2020
by Tom Igoe

*/

// include the various libraries that you'll use:
let SerialPort = require('serialport');			// include the serialport library
let	portName =  process.argv[2];						// get the port name from the command line
let WebSocketServer = require('ws').Server;   // include the webSocket library

// configure the webSocket server:
const SERVER_PORT = 8081;                 // port number for the webSocket server
let wss = new WebSocketServer({port: SERVER_PORT}); // the webSocket server
let connections = new Array;            // list of connections to the server

let myPort = new SerialPort(portName, 9600);// open the port
let Readline = SerialPort.parsers.Readline;	// make instance of Readline parser
let parser = new Readline();								// make a new parser to read ASCII lines
myPort.pipe(parser);													// pipe the serial stream to the parser

// these are the definitions for the serial events:
myPort.on('open', showPortOpen);    // called when the serial port opens
myPort.on('close', showPortClose);  // called when the serial port closes
myPort.on('error', showError);   // called when there's an error with the serial port
parser.on('data', readSerialData);  // called when there's new data incoming


// ------------------------ Serial event functions:
// this is called when the serial port is opened:
function showPortOpen() {
  console.log('port open. Data rate: ' + myPort.baudRate);
}

// this is called when new data comes into the serial port:
function readSerialData(data) {
  // if there are webSocket connections, send the serial data
  // to all of them:
  console.log(data);
  if (connections.length > 0) {
    broadcast(data);
  }
}

function showPortClose() {
   console.log('port closed.');
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
    let position = connections.indexOf(client); // get the client's position in the array
    connections.splice(position, 1);        // and delete it from the array
  });
}
// This function broadcasts messages to all webSocket clients
function broadcast(data) {
  for (c in connections) {     // iterate over the array of connections
    connections[c].send(JSON.stringify(data)); // send the data to each connection
  }
}
