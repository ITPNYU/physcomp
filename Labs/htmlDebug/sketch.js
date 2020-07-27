var logDisplay;		// an HTML element for displaying log data
var hidden = false; // whether the log display  is hidden or not


function setup() {
	createCanvas(windowWidth, windowHeight);
	// create some HTML elements to manage log display:
	createHTML();
}

function draw() {
	background('#FFDDDD');
	// if the key is pressed, display it
	if (keyIsPressed) {
		printData('key pressed: ' + key);
	}
}

// show or hide the log display by typing shift-spacebar:
function keyPressed() {
	if (keyIsDown(SHIFT) && key == ' ') {
		if (hidden) {
			logDisplay.show();
		} else {
			logDisplay.hide();
		}
		hidden = !hidden;
	}
}

// create some HTML elements in the sketch:
function createHTML() {
	logDisplay = createElement('div', 'incoming data goes here');
	logDisplay.attribute('aria-label', 'incoming data');
	logDisplay.attribute('aria-role', 'alert');
	logDisplay.attribute('aria-live', 'polite');
	logDisplay.position(10, 40);
}

function printData(inString) {
	// put the input in the logDisplay div:
	logDisplay.html('log: ' + inString);
	// print it to the console as well
	console.log(inString);
}