var logDisplay;		// an HTML element for displaying log data
var hidden = false; // whether the log display  is hidden or not


function setup() {
	createCanvas(windowWidth, windowHeight);
	// create some HTML elements to manage log display:
	createHTML();
}

function draw() {
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
	// get the DOM element for showing debug data:
	logDisplay = document.getElementById('logDiv');
	// convert it to a p5.elt so we can use the p5 DOM functions on it:
	logDisplay = new p5.Element(logDisplay);
}

function printData(inString) {
	// put the input in the logDisplay div:
	logDisplay.html('log: ' + inString);
	// print it to the console as well
	console.log(inString);
}