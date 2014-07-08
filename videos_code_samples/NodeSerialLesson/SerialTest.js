var serialport = require("serialport"),	// include the serialport library
	SerialPort  = serialport.SerialPort,	// make a local instance of it
	portName = process.argv[2],				// get the serial port name from the command line
	ledState = false;

// open the serial port. The portname comes from the command line:
var myPort = new SerialPort(portName, { 
	baudRate: 9600,
	// add an option in the serial port object 
	// so that you can keep track of whether or not the serial port is open:
	options: false,
	// look for return and newline at the end of each data packet:
	parser: serialport.parsers.readline("\r\n")
});
 
// called when the serial port opens:
myPort.on('open', function() {
	console.log('port open');
	// set options.open so you can track the port statue:
	myPort.options.open = true;
});

// called when the serial port closes:
myPort.on('close', function() {
	console.log('port closed');
	// set options.open so you can track the port statue:
	myPort.options.open = false;
});

// called when there's an error with the serial port:
myPort.on('error', function(error) {
	console.log('there was an error with the serial port: ' + error);
	myPort.close();
});

// called when there's new incoming serial data:  
myPort.on('data', function (data) {
	console.log(data);   // print the incoming data
   myPort.write('x');   // send back a byte in response

});
