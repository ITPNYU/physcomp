
var serial;       // Declare a "SerialPort" object
var serialDiv;  // a div to show the serial input
var portName = '/dev/cu.usbmodem141231'; // fill in your serial port name here
var osc;

function setup() {
	createCanvas(windowWidth, windowHeight);
	createHTML();
	// open an instance of serialport and set up event handlers:
	serial = new p5.SerialPort();
	serial.on('data', serialEvent);
	// open the port:
	serial.open(portName);
	// notify the user in the HTML div:
	serialDiv.html('Serial port ' + portName + ' is open.')
	osc = new p5.Oscillator();
	osc.start(0, 440);
}

function draw() {
	// blue background:
	background('#3472DD');
}

function createHTML() {
	// create a div to put the incoming serial data into:
	serialDiv = createElement('div', 'serial incoming data goes here');
	serialDiv.attribute('aria-role', 'alert');
	serialDiv.attribute('aria-live', 'polite');
	serialDiv.style('color', 'white');
	serialDiv.position(10, 40);
}

// toggle the loudness on and off when you hit the space bar:
function keyReleased() {
	// get the current loudness value:
	var loudness = osc.amp().value;
	// if the user hits the spacebar:
	if (key == ' ') {
		// if the loudness is > 0, turn it off:
		if (loudness > 0) {
			osc.amp(0);
		} else {
			// if the loudness is 0, turn it on:
			osc.amp(0.5);
		}
	}
}
function serialEvent() {
	// read serial input:
	var inString = serial.readStringUntil('\r\n');
	// trim any whitespace:
	trim(inString);
	// if there's no string, quit this function:
	if (!inString) return;
	// put the result in the serialInput div:
	serialDiv.html(inByte);
	console.log(inByte);
	var pitch = Number(inString);
	osc.freq(pitch, 0, 0);
}