/*
	
	
	created 19 Sept 2014
	by Tom Igoe

*/

var servi = require('servi'),
 	serialport = require('serialport'),	 // include the serialport library
	SerialPort  = serialport.SerialPort, // make a local instance of it
	portName = process.argv[2],			 // get the serial port name from the command line
	latestData = "-1";						 // latest data from the serial port
	
var app = new servi(false);		// servi instance
app.port(8080);						// port number to run the server on

// configure the server's behavior:
app.serveFiles("public");			// serve all static HTML files from /public
app.route('/data', sendData);		// route requests for /data to sendData() function

// start serial communications. if you've got a serial port name, open it:
if (portName == null) {
	// if the user doesn't give a serial port when they launch this script,
	// tell them, then quit the program:
	console.log("\nYou need to enter the serial port name when you start this script.")
	console.log("Choose from the ports below and type \'node index.js portname\'\n");
	process.exit(1);		// quit the program
} else {
	// open the serial port:
	var myPort = new SerialPort(portName, { 
		baudRate: 9600,
		// look for return and newline at the end of each data packet:
		parser: serialport.parsers.readline("\r\n") 
	});
}


// configure the serial port's behavior:
myPort.on('open', showPortOpen);		// when the port opens, call the showPortOpen function  
myPort.on('data', saveLatestData);	// when new data comes in, call the saveLatestData function


// now that everything is configured, start the server:
app.start();						  


// ------------------------ Serial Port functions 

// called by the myport.on(open) function:
function showPortOpen() {
	// print out the fact that the port opened:
	console.log('port open. Data rate: ' + myPort.options.baudRate);
}

// called by the myport.on(data) function:
function saveLatestData(data) {
	// save the latest serial string in a global variable
	// so that other functions can use it:
	latestData = data;
}

// ------------------------ Server functions 
function sendData(request) {	
	// print out the fact that a client HTTP request came in to the server:
	console.log("Got a client request, sending them the data.");
	// respond to the client request with the latest serial string:
   request.respond(latestData);
}


