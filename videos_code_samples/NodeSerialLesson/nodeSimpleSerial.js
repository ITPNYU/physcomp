var serialport = require('serialport'),
   SerialPort = serialport.SerialPort,
   portname = process.argv[2];      // for the serial port name from the command line
   
var myPort = new SerialPort(portname, {
   baudRate: 9600,
   options: false,
   parser: serialport.parsers.readline("\r\n")   
});
   
myPort.on('open', function() {
   console.log('port is open');
});

myPort.on('close', function () {
   console.log('port is closed');
});

myPort.on('error', function() {
   console.log ('holy serialport, Batman! Something went wrong!');
});

myPort.on('data', function(data) {
   console.log(data);
   myPort.write('x');
});

