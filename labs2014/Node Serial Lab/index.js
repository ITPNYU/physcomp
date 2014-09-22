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
app.serveFiles("public");			// serve all static HTML files from /public
app.route('/data', sendData);		// route requests for /data to sendData() function
app.start();						   // start the server

// if you've got a serial port name, open it:
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

// ------------------------ Serial Port functions 

// called when the serial port opens:
myPort.on('open', function() {
	console.log('port open. Data rate: ' + myPort.options.baudRate);
});

// called when there's new incoming serial data:  
myPort.on('data', function (data) {
	latestData = data;
});

// ------------------------ Server functions 
function sendData(request) {
    request.respond(latestData);
}


